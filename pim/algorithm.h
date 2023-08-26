#ifndef CUDAPIM_ALGORITHM_H
#define CUDAPIM_ALGORITHM_H

#include "driver.h"
#include "vector.h"

namespace pim {

    /**
     * Computes the reduction sum of the given vector
     * @tparam T
     * @param x
     * @return
     */
    template <class T>
    T sum(const pim::vector<T>& x){

        // Intra-warp reduction
        pim::vector<T> z = x;
        for(pim::size_t j = 0; (1 << j) < pim::warpSize(); j++) {
            pim::vector<T> y = ~z;
            for (int i = 0; i < (pim::warpSize() >> (j + 1)); i++) {
                y.warpMove(i + (pim::warpSize() >> (j + 1)), i);
            }
            z = z + y;
        }

        // Inter-warp reduction
        T output = z[0];
        for(pim::size_t i = pim::warpSize(); i < z.size(); i += pim::warpSize()){
            output += z[i];
        }

        return output;

    }

    /**
     * Performs a warp-parallel broadcast from the first thread in each warp to all other threads
     * @tparam T
     * @param x
     * @return
     */
    template <class T>
    pim::vector<T> warpBroadcast(const pim::vector<T>& x){

        // Intra-warp broadcast
        pim::vector<T> output = ~x;
        for(pim::size_t i = 1; i < pim::warpSize(); i++) {
            output.warpMove(0, i);
        }
        return output;

    }

    /**
     * Performs a warp-parallel shift
     * @tparam T
     * @param x
     * @param distance
     * @return
     */
    template <class T>
    pim::vector<T> warpShift(const pim::vector<T>& x, size_t distance){

        if(distance == 0) return x;

        // Intra-warp shift
        pim::vector<T> output = ~x;
        if(distance > 0) {
            for (pim::size_t i = pim::warpSize() - distance; i >= 0; i--) {
                output.warpMove(i, i + distance);
            }
        }
        else{
            for (pim::size_t i = -distance; i < pim::warpSize(); i++) {
                output.warpMove(i, i + distance);
            }
        }
        return output;

    }

}

#endif // CUDAPIM_ALGORITHM_H
