# CUDA-PIM: End-to-End Integration of Digital Processing-in-Memory from High-Level C++ to Microarchitectural Design
## Overview
This repository includes the framework proposed in the following paper,

`Anonymous Authors, “CUDA-PIM: End-to-End Integration of Digital Processing-in-Memory from High-Level C++ to Microarchitectural Design,” 2023.`

The framework enables high-level programming of PIM applications with significant ease. The framework benefits from the high
flexibility of C++ to enable the user to assemble new PIM routines from existing arithmetic functions, such as:
```
#include "pim/vector.h"

pim::vector<float> myFunc(const pim::vector<float>& x,
        const pim::vector<float>& y){
    return x * y + x;
}
```
Further, the PIM operations can be interleaved within existing larger CPU/GPU programs. This is possible due to familiar
bindings for read/write operations; for example, `x[5] = input_from_user()` will execute `input_from_user` on the CPU host
and then write the result to the PIM vector `x ` by automatically generating a write micro-operation. 

More complex applications such as matrix multiplication and 2D matrix convolution also enjoy a drastic simplification 
compared to their original implementations (see [FourierPIM](https://github.com/oleitersdorf/FourierPIM) and [MatPIM](https://github.com/oleitersdorf/MatPIM)):
```
/**
 * Proposed PIM matrix-vector multiplication
 * @tparam T
 */
template <class T>
pim::vector<T> pimMatrixVectorMultiplication(std::vector<pim::vector<T>> A, pim::vector<T> x){

    // Allocate output vector
    pim::vector<T> output(m);

    // Iterate over the columns of A
    for(int i = 0; i < n; i++){
        pim::vector<T> temp(m, x[i]);
        output = output + A[i] * temp;
    }
    return output;

}
```
```
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
            // Add A (shifted by ki) * K[ki][kj] to out
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
```

The repository is split into four parts: (1) the underlying GPU-accelerated simulator, (2) the microarchitectural driver, (3) the development library,
and (4) a series of test scripts that include example applications such as matrix multiplication, matrix convolution, and the Fast Fourier Transform.

## User Information
### Dependencies
The simulation environment is implemented via `CUDA` to enable fast execution of many samples in parallel. Therefore,
the project requires the following libraries:
1. CUDA 12.0 (with a capable GPU of at least 8GB DRAM)
2. CMAKE 3.19 (or higher)
3. Compiler for C++ 17 (or higher)

### Organization
The repository is organized into the following directories:
- `pim`: this directory contains the source code for the simulator, driver, and library.
- `tests`: this directory contains the source code for the tests.
- `main.cpp`: this file may be edited and compiled for interactive testing.

# Instruction-Set-Architecture (ISA)

The full instruction-set-architecture (ISA) supported in CUDA-PIM is as follows:

| Operation                  | Int Support | Float Support |
|----------------------------|:-----------:|:-------------:|
| **Arithmetic**             |             |               |
| Addition                   | &#10003;    | &#10003;      |
| Subtraction                | &#10003;    | &#10003;      |
| Multiplication             | &#10003;    | &#10003;      |
| Division                   | &#10003;    | &#10003;      |
| Modulo                     | &#10003;    |               |
| Negation                   | &#10003;    | &#10003;      |
| **Comparison**             |             |               |
| Less than (or equal to)    | &#10003;    | &#10003;      |
| Greater than (or equal to) | &#10003;    | &#10003;      |
| Equal                      | &#10003;    | &#10003;      |
| **Bitwise**                |             |               |
| Bitwise Not                | &#10003;    | &#10003;      |
| Bitwise And                | &#10003;    | &#10003;      |
| Bitwise Or                 | &#10003;    | &#10003;      |
| Bitwise Xor                | &#10003;    | &#10003;      |
| **Miscellaneous**          |             |               |
| Sign                       | &#10003;    | &#10003;      |
| Zero                       | &#10003;    | &#10003;      |
| Abs                        | &#10003;    | &#10003;      |
