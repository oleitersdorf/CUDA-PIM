#include <iostream>
#include <vector>
#include <cassert>

#include "../pim/vector.h"
#include "../pim/algorithm.h"

/**
 * Baseline CPU matrix-vector multiplication
 * @tparam T
 */
template <class T>
std::vector<T> cpuMatrixMultiplication(std::vector<std::vector<T>> A, std::vector<T> x){

    // Verify dimensions match
    size_t n = A.size();
    size_t m = A[0].size();
    assert(n == x.size());

    // Allocate output
    std::vector<T> out(m);

    // Sum over products
    for(int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            out[i] += A[j][i] * x[j];
        }
    }

    return out;

}

/**
 * Proposed PIM matrix-vector multiplication
 * @tparam T
 */
template <class T>
pim::vector<T> pimMatrixMultiplication(std::vector<pim::vector<T>> A, pim::vector<T> x){

    // Verify dimensions match
    size_t n = A.size();
    size_t m = A[0].size();
    assert(n == x.size());

    // Allocate output vector
    pim::vector<T> output(m);

    // Iterate over the columns of A
    for(int i = 0; i < n; i++){
        pim::vector<T> temp(m, x[i]);
        output = output + A[i] * temp;
    }

    return output;

}

/**
 * Baseline CPU matrix convolution
 * @tparam T
 */
template <class T>
std::vector<std::vector<T>> cpuMatrixConvolution(std::vector<std::vector<T>> A, std::vector<std::vector<T>> K){

    // Allocate output matrix
    std::vector<std::vector<T>> out(A.size(), std::vector<T>(A[0].size()));

    // Compute by iterating over output cells
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < A[0].size(); j++){
            // Iterate over kernel
            for(int ki = 0; ki < K.size(); ki++){
                for(int kj = 0; kj < K[0].size(); kj++){
                    if(i + ki < A.size() && j + kj < A[0].size()) out[i][j] += A[i + ki][j + kj] * K[ki][kj];
                }
            }

        }
    }

    return out;

}

/**
 * Proposed PIM matrix convolution
 * @tparam T
 */
template <class T>
std::vector<pim::vector<T>> pimMatrixConvolution(std::vector<pim::vector<T>> A, std::vector<std::vector<T>> K){

    // Allocate output matrix
    std::vector<pim::vector<T>> out(A.size(), pim::vector<T>(A[0].size()));

    // Compute by iterating over kernel cells, and performing in parallel across matrix columns
    for(int kj = 0; kj < K[0].size(); kj++){
        for(int ki = 0; ki < K.size(); ki++){
            pim::vector<T> temp(A[0].size(), K[ki][kj]);
            for(int i = 0; i + ki < A.size(); i++){
                out[i] = out[i] + A[i + ki] * temp;
            }
        }

        // Shift matrix up
        for(int i = 0; i < A.size(); i++) {
            A[i] = pim::warpShift(A[i], -1);
            A[i][A[0].size() - 1] = 0;
        }

    }

    return out;

}

void testMatrixMultiplication(){

    // Generate input data
    int N = 8, M = 1024;
    std::vector<std::vector<int>> A(N, std::vector<int>(M));
    for(int i = 0; i < M; i++) for(int j = 0; j < N; j++) A[j][i] = rand();
    std::vector<int> x(N);
    for(int j = 0; j < N; j++) x[j] = rand();
    // Copy input data to PIM
    std::vector<pim::vector<int>> d_A;
    for(int j = 0; j < N; j++) d_A.emplace_back(A[j]);
    pim::vector<int> d_x = x;

    // Perform both CPU and PIM algorithms
    std::vector<int> res = cpuMatrixMultiplication(A, x);
    pim::vector<int> d_res = pimMatrixMultiplication(d_A, d_x);

    // Compare results
    for(int i = 0; i < M; i++){
        assert(res[i] == d_res[i]);
    }

    std::cout << "Passed Matrix Multiplication Test!" << std::endl;

}

void testMatrixConvolution(){

    // Generate input data
    int n = 4, m = 512, k = 3;
    std::vector<std::vector<int>> A(n, std::vector<int>(m));
    for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) A[j][i] = rand();
    std::vector<std::vector<int>> K(k, std::vector<int>(k));
    for(int i = 0; i < k; i++) for(int j = 0; j < k; j++) K[i][j] = rand();
    // Copy input data to PIM
    std::vector<pim::vector<int>> d_A;
    for(int j = 0; j < n; j++) d_A.emplace_back(A[j]);

    // Perform both CPU and PIM algorithms
    std::vector<std::vector<int>> res = cpuMatrixConvolution(A, K);
    std::vector<pim::vector<int>> d_res = pimMatrixConvolution(d_A, K);

    // Compare results
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            assert(res[i][j] == d_res[i][j]);
        }
    }

    std::cout << "Passed Matrix Convolution Test!" << std::endl;

}

int main() {

    testMatrixMultiplication();
    testMatrixConvolution();

    return 0;

}
