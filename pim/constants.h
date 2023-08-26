#ifndef CUDAPIM_CONSTANTS_H
#define CUDAPIM_CONSTANTS_H

#include <cstdint>

namespace pim {

    /** Generic type representing a size */
    typedef int64_t size_t;

    /** The data type for read/write operations */
    typedef uint32_t dtype;

    /** The data type representing micro-operations */
    typedef uint64_t otype;

    /** The log of the total number of crossbars in the memory */
    constexpr size_t LOG_NUM_CROSSBARS = 16;
    /** Total number of crossbars in the memory */
    constexpr size_t NUM_CROSSBARS = 1 << LOG_NUM_CROSSBARS;
    /** A mask of LOG_NUM_CROSSBARS bits at the LSB */
    constexpr otype NUM_CROSSBARS_MASK = (1 << LOG_NUM_CROSSBARS) - 1;

    /** The log of the width of every crossbar in the memory */
    constexpr size_t LOG_CROSSBAR_WIDTH = 10;
    /** The width of every crossbar in the memory */
    constexpr size_t CROSSBAR_WIDTH = 1 << LOG_CROSSBAR_WIDTH;

    /** The log of the height of every crossbar in the memory */
    constexpr size_t LOG_CROSSBAR_HEIGHT = 10;
    /** The height of every crossbar in the memory */
    constexpr size_t CROSSBAR_HEIGHT = 1 << LOG_CROSSBAR_HEIGHT;
    /** A mask of LOG_CROSSBAR_HEIGHT bits at the LSB */
    constexpr otype CROSSBAR_HEIGHT_MASK = (1 << LOG_CROSSBAR_HEIGHT) - 1;

    /** The log of the number of horizontal partitions in every crossbar of the memory */
    constexpr size_t LOG_CROSSBAR_N = 5;
    /** The number of horizontal partitions in every crossbar of the memory */
    constexpr size_t CROSSBAR_N = 1 << LOG_CROSSBAR_N;
    /** A mask of LOG_CROSSBAR_N bits at the LSB */
    constexpr otype CROSSBAR_N_MASK = (1 << LOG_CROSSBAR_N) - 1;

    /** The log of the number of registers per row */
    constexpr size_t LOG_CROSSBAR_R = LOG_CROSSBAR_WIDTH - LOG_CROSSBAR_N;
    /** The number of registers per row */
    constexpr size_t CROSSBAR_R = 1 << LOG_CROSSBAR_R;
    /** A mask of LOG_CROSSBAR_R bits at the LSB */
    constexpr otype CROSSBAR_R_MASK = (1 << LOG_CROSSBAR_R) - 1;

    /**
     * Represents a generic range-based mask (e.g., {start, start + step, ..., stop}, inclusive)
     */
    struct RangeMask {
        size_t start, stop, step;

        /** Mask constructor */
        RangeMask (size_t start, size_t stop, size_t step) : start(start), stop(stop), step(step) {}

        /** Mask comparison */
        bool operator==(RangeMask const& other) const {return start == other.start && stop == other.stop && step == other.step;}
        bool operator!=(RangeMask const& other) const {return !(*this == other);}
    };
    /** A mask for all rows */
    #define ALL_ROWS RangeMask(0, CROSSBAR_HEIGHT - 1, 1)
    /** A mask for all crossbars */
    #define ALL_CROSSBARS RangeMask(0, NUM_CROSSBARS - 1, 1)

    /**
     * The different types of micro-operations
     */
    enum MicrooperationType{
        READ, WRITE, LOGIC, MASK
    };

    /**
     * The possible gates types that are supported
     */
    enum GateType{
        INIT0, INIT1, NOT, NOR
    };

    /**
     * Represents a vector address in the memory. A nullptr is represented with reg = -1.
     */
    struct address {

        /** The interval [startArray, endArray] of arrays containing the address */
        size_t startArray, endArray;

        /** The register address of the address */
        size_t reg;

    };

}

#endif // CUDAPIM_CONSTANTS_H
