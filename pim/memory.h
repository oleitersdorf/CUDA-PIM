#ifndef CUDAPIM_MEMORY_H
#define CUDAPIM_MEMORY_H

#include <vector>
#include "constants.h"

namespace pim{

    /**
     * Allocates a vector of size n
     * @param n
     * @return
     */
    address malloc(size_t n);

    /**
     * Allocates several vectors of size n
     * @param n
     * @param m
     * @return
     */
    std::vector<address> malloc(size_t n, size_t m);

    /**
     * Frees the memory allocates for the given vector
     * @param vec
     */
    void free(address vec);

}

#endif // CUDAPIM_MEMORY_H
