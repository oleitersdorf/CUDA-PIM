#include <iostream>
#include <vector>
#include <complex>
#include "../pim/vector.h"

struct complexVec{

    pim::vector<float> real, imag;

    explicit complexVec(pim::size_t n) : real(pim::vector<float>(n)), imag(pim::vector<float>(n)) {}

    complexVec(const pim::vector<float>& real, const pim::vector<float>& imag) : real(real), imag(imag) {}

};

/**
 * Proposed PIM complex addition
 * @param x
 * @param y
 * @return
 */
complexVec add(const complexVec& x, const complexVec& y){
    return {x.real + y.real, x.imag + y.imag};
}

/**
 * Proposed PIM complex subtraction
 * @param x
 * @param y
 * @return
 */
complexVec subtract(const complexVec& x, const complexVec& y){
    return {x.real - y.real, x.imag - y.imag};
}

/**
 * Proposed PIM complex multiplication
 * @param x
 * @param y
 * @return
 */
complexVec multiply(const complexVec& x, const complexVec& y){
    return {x.real * y.real - x.imag * y.imag, x.real * y.imag + x.imag * y.real};
}

/**
 * Proposed PIM complex in-place butterfly operation
 * @param u
 * @param v
 * @param w
 * @return
 */
void butterfly(complexVec& u, complexVec& v, const complexVec& w){
    complexVec wv = multiply(w, v);
    v = subtract(u, wv);
    u = add(u, wv);
}

/**
 * Bit-reverse routine
 * @param x
 * @param N
 * @return
 */
unsigned int bitRev(unsigned int x, int N) {
    unsigned int bitReversed = 0;
    for (int i = 0; i < N; ++i) {
        bitReversed |= ((x >> i) & 1) << (N - 1 - i);
    }
    return bitReversed;
}

/**
 * Proposed PIM complex FFT
 * @tparam T
 */
complexVec fft(complexVec x){
    pim::size_t n = x.real.n;

    // Pre-compute the constants
    std::vector<std::complex<float>> w;
    for(int i = 0; i < n; ++i) {
        std::complex<float> complex_num = std::exp(std::complex<float>(0.0f, -2.0f * M_PI * static_cast<float>(i) / static_cast<float>(n)));
        w.push_back(complex_num);
    }

    // Bit-reversal permutation
    for(int k = 0; k < n; k++){
        int j = bitRev(k, round(log2(n)));
        if(k < j){
            float temp = x.real[k];
            x.real[k] = x.real[j];
            x.real[j] = temp;
            temp = x.imag[k];
            x.imag[k] = x.imag[j];
            x.imag[j] = temp;
        }
    }

    complexVec d_w(n);

    for(int k = 0; (1 << k) < n; k++){
        pim::vector<int> mask(n);

        // Shift right, upwards
        complexVec y(n); y.real = ~x.real; y.imag = ~x.imag;
        for(int i = 0; i < n; i++){
            if (i & (1 << k)){
                y.real.warpMove(i, i - (1 << k));
                y.imag.warpMove(i, i - (1 << k));
                mask[i] = -1;
            }
        }

        // Write the constants
        for(int i = 0; i < n; i++){
            if(!(i & (1 << k))){
                d_w.real[i] = w[(i % (1 << k)) * (n / (1 << (1 + k)))].real();
                d_w.imag[i] = w[(i % (1 << k)) * (n / (1 << (1 + k)))].imag();
            }
        }

        // Perform the butterfly operation
        butterfly(x, y, d_w);

        // Shift downwards, left
        for(int i = 0; i < n; i++){
            if (i & (1 << k)){
                y.real.warpMove(i - (1 << k), i);
                y.imag.warpMove(i - (1 << k), i);
            }
        }
        x.real = x.real & ~mask; x.imag = x.imag & ~mask;
        y.real = (~y.real) & mask; y.imag = (~y.imag) & mask;
        x.real = x.real | y.real; x.imag = x.imag | y.imag;

    }

    return x;

}

int main() {

    // Generate input data
    int n = 8;
    complexVec x(n);
    for(int i = 0; i < n; i++){
        x.real[i] = float(rand()) / float(RAND_MAX);
        x.imag[i] = float(rand()) / float(RAND_MAX);
    }
    std::cout << "[";
    for(int i = 0; i < n; i++){
        std::cout << x.real[i] << " + 1j * " << x.imag[i] << ",";
    }
    std::cout << "]" << std::endl;

    // Perform FFT
    complexVec y = fft(x);

    // Verify results
    std::cout << "[";
    for(int i = 0; i < n; i++){
        std::cout << y.real[i] << " + 1j * " << y.imag[i] << ",";
    }
    std::cout << "]";

    return 0;

}
