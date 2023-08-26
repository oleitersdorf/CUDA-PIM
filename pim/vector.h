#ifndef CUDAPIM_VECTOR_H
#define CUDAPIM_VECTOR_H

#include <iostream>
#include <vector>
#include "constants.h"
#include "memory.h"
#include "driver.h"

namespace pim {

    /**
     * PIM vector of type T
     * @tparam T
     */
    template <typename T>
    class vector {

    public:

        /** The total length of the vector */
        size_t n;

        /** The memory address of the vector */
        address vec;

        /** The current row mask */
        RangeMask curr_mask = ALL_ROWS;

        /**
         * Constructs and allocates an empty vector
         * @param n
         */
        explicit vector(size_t n, T val = T()) : n(n), vec(malloc(n)){
            write({vec.startArray, vec.endArray, 1}, vec.reg, curr_mask, val);
        }

        /**
         * Constructs the vector as a copy of the given std::vector
         * @param other
         */
        vector(const vector& other) : n(other.n), vec(malloc(n)) {
            copy(other.vec.reg, vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
        }

        /**
         * Constructs the vector as a copy of the given vector
         * @param other
         */
        vector(const std::vector<T>& other) : n(other.size()), vec(malloc(n)) {
            for(size_t i = 0; i < n; i++){
                (*this)[i] = other[i];
            }
        }

        /**
         * Move constructor
         * @param other
         */
        vector(vector&& other)  noexcept : n(other.n), vec(other.vec) {
            other.vec.reg = -1;
        }

        /**
         * Assignment operator
         * @param other
         * @return
         */
        vector& operator=(const vector& other){
            if(this == &other)
                return *this;
            copy(other.vec.reg, vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return *this;
        }

        /**
         * Assignment operator
         * @param other
         * @return
         */
        vector& operator=(const std::vector<T>& other){
            for(size_t i = 0; i < n; i++){
                (*this)[i] = other[i];
            }
            return *this;
        }

        /**
         * Frees the vector
         */
        ~vector(){
            free(vec);
        }

        /**
         * Returns the size of the vector
         * @return
         */
        size_t size(){
            return n;
        }

        /**
         * A reference to an element in the vector (used to support vec[x] = y)
         */
        class reference{
            friend class vector;

            /** The belonging vector */
            vector& vec;
            /** The position in the vector */
            size_t pos;

            /** Allocates the reference given the vector and position */
            reference(vector& vec, size_t pos) : vec(vec), pos(pos){}

        public:

            /**
             * Performs a standard write operation to the vector at the given entry
             * @param x
             * @return
             */
            reference& operator=(T x){
                write(vec.vec.startArray + pos / pim::warpSize(), vec.vec.reg, pos % pim::warpSize(), reinterpret_cast<dtype &>(x));
                return *this;
            }

            /**
             * Performs a standard write operation to the vector at the given entry
             * @param x
             * @return
             */
            reference& operator=(const reference& other){
                T val = *other;
                write(vec.vec.startArray + pos / pim::warpSize(), vec.vec.reg, pos % pim::warpSize(), reinterpret_cast<dtype &>(val));
                return *this;
            }

            /**
             * Performs a standard read operation to the vector at the given entry
             * @return
             */
            operator T() const{
                dtype res = read(vec.vec.startArray + pos / pim::warpSize(), vec.vec.reg, pos % pim::warpSize());
                return reinterpret_cast<T &>(res);
            }

            reference& operator++(){
                pos++;
                return *this;
            }
            T operator*() const{
                dtype res = read(vec.vec.startArray + pos / pim::warpSize(), vec.vec.reg, pos % pim::warpSize());
                return reinterpret_cast<T &>(res);
            }

            friend bool operator== (const reference& a, const reference& b) { return a.pos == b.pos; };
            friend bool operator!= (const reference& a, const reference& b) { return a.pos != b.pos; };

        };

        /**
         * Returns a reference to the given element
         * @param pos
         * @return
         */
        reference operator[](size_t pos){
            return reference(*this, pos);
        }
        /**
         * Reads the element at the given position
         * @param pos
         * @return
         */
        T operator[](size_t pos) const{
            dtype res = read(vec.startArray + pos / pim::warpSize(), vec.reg, pos % pim::warpSize());
            return reinterpret_cast<T &>(res);
        }

        reference begin() {
            return reference(*this, 0);
        }
        reference end(){
            return reference(*this, n);
        }

        /**
         * Performs element-parallel addition with another vector
         * @param other
         * @return
         */
        vector operator+(const vector& other) const{
            vector res(n);
            add<T>(vec.reg, other.vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel negation
         * @return
         */
        vector operator-() const{
            vector res(n);
            negate<T>(vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel absolute value
         * @return
         */
        vector abs() const{
            vector res(n);
            absolute<T>(vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel subtraction with another vector
         * @param other
         * @return
         */
        vector operator-(const vector& other) const{
            vector res(n);
            subtract<T>(vec.reg, other.vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel multiplication with another vector
         * @param other
         * @return
         */
        vector operator*(const vector& other) const{
            vector res(n);
            multiply<T>(vec.reg, other.vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel division with another vector
         * @param other
         * @return
         */
        vector operator/(const vector& other) const{
            vector res(n);
            divide<T>(vec.reg, other.vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel modulo division with another vector
         * @param other
         * @return
         */
        vector operator%(const vector& other) const{
            vector res(n);
            modulo<T>(vec.reg, other.vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel bitwise NOT
         * @param other
         * @return
         */
        vector operator~() const{
            vector res(n);
            bitwiseNot(vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel bitwise OR with another vector
         * @param other
         * @return
         */
        template <class O>
        vector operator|(const vector<O>& other) const{
            vector res(n);
            bitwiseOr(vec.reg, other.vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel bitwise AND with another vector
         * @param other
         * @return
         */
        template <class O>
        vector operator&(const vector<O>& other) const{
            vector res(n);
            bitwiseAnd(vec.reg, other.vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel bitwise XOR with another vector
         * @param other
         * @return
         */
        template <class O>
        vector operator^(const vector<O>& other) const{
            vector res(n);
            bitwiseXor(vec.reg, other.vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs an element-parallel operation that returns the signs of the given numbers
         * @param other
         * @return
         */
        vector<int> sign() const{
            vector<int> res(n);
            pim::sign<T>(vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs an element-parallel operation that returns whether the given numbers are zero
         * @param other
         * @return
         */
        vector<int> zero() const{
            vector<int> res(n);
            pim::zero<T>(vec.reg, res.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return std::move(res);
        }

        /**
         * Performs element-parallel comparison with another vector
         * @param other
         * @return
         */
        vector<int> operator<(const vector& other) const{
            vector temp(n);
            subtract<T>(vec.reg, other.vec.reg, temp.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return temp.sign();
        }

        /**
         * Performs element-parallel comparison with another vector
         * @param other
         * @return
         */
        vector<int> operator<=(const vector& other) const{
            vector temp(n);
            subtract<T>(vec.reg, other.vec.reg, temp.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return temp.sign() | temp.zero();
        }

        /**
         * Performs element-parallel comparison with another vector
         * @param other
         * @return
         */
        vector<int> operator>(const vector& other) const{
            vector temp(n);
            subtract<T>(other.vec.reg, vec.reg, temp.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return temp.sign();
        }

        /**
         * Performs element-parallel comparison with another vector
         * @param other
         * @return
         */
        vector<int> operator>=(const vector& other) const{
            vector temp(n);
            subtract<T>(other.vec.reg, vec.reg, temp.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return temp.sign() | temp.zero();
        }

        /**
         * Performs element-parallel comparison with another vector
         * @param other
         * @return
         */
        vector<int> operator==(const vector& other) const{
            vector temp(n);
            subtract<T>(vec.reg, other.vec.reg, temp.vec.reg, {vec.startArray, vec.endArray, 1}, curr_mask);
            return temp.zero();
        }

        /**
         * Performs an intra-warp warp-parallel move operation in all of the warps containing the vector
         * @param inputThread
         * @param outputThread
         */
        void warpMove(size_t inputThread, size_t outputThread){
            pim::warpMove(inputThread, outputThread, vec.reg, {vec.startArray, vec.endArray, 1});
        }

        /**
         * Sets the mask for subsequent operations on the vector
         */
        void setMask(RangeMask mask) {
            curr_mask = mask;
        }

    };

}

#endif // CUDAPIM_VECTOR_H
