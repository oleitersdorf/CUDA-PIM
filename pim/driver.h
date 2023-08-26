#ifndef CUDAPIM_DRIVER_H
#define CUDAPIM_DRIVER_H

#include "constants.h"

namespace pim{

    /**
     * Read macro-instruction
     * @param crossbar
     * @param reg
     * @param row
     * @return
     */
    dtype read(size_t crossbar, size_t reg, size_t row);

    /**
     * Write macro-instruction
     * @param crossbar
     * @param reg
     * @param row
     * @param data
     * @return
     */
    void write(size_t crossbar, size_t reg, size_t row, dtype data);

    /**
     * Write macro-instruction to potentially several rows
     * @param crossbars
     * @param reg
     * @param rows
     * @param data
     */
    void write(RangeMask crossbars, size_t reg, RangeMask rows, dtype data);

    /**
     * Performs addition on the given registers
     * @param regX
     * @param regY
     * @param regZ
     * @param crossbars
     * @param rows
     */
    template <class T>
    void add(size_t regX, size_t regY, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs negation on the given register
     * @param regX
     * @param regZ
     * @param crossbars
     * @param rows
     */
    template <class T>
    void negate(size_t regX, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs absolute value on the given register
     * @param regX
     * @param regZ
     * @param crossbars
     * @param rows
     */
    template <class T>
    void absolute(size_t regX, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs subtraction on the given registers
     * @param regX
     * @param regY
     * @param regZ
     * @param crossbars
     * @param rows
     */
    template <class T>
    void subtract(size_t regX, size_t regY, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs multiplication on the given registers
     * @param regX
     * @param regY
     * @param regZ
     * @param crossbars
     * @param rows
     */
    template <class T>
    void multiply(size_t regX, size_t regY, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs division on the given registers
     * @param regX
     * @param regY
     * @param regZ
     * @param crossbars
     * @param rows
     */
    template <class T>
    void divide(size_t regX, size_t regY, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs modulo division on the given registers
     * @param regX
     * @param regY
     * @param regZ
     * @param crossbars
     * @param rows
     */
    template <class T>
    void modulo(size_t regX, size_t regY, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Returns the sign of the given register
     * @param regX
     * @param regZ
     * @param crossbars
     * @param rows
     */
    template <class T>
    void sign(size_t regX, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Returns whether the given register is all-zero
     * @param regX
     * @param regZ
     * @param crossbars
     * @param rows
     */
    template <class T>
    void zero(size_t regX, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs bitwise NOT on the given register
     * @param regX
     * @param regZ
     * @param crossbars
     * @param rows
     */
    void bitwiseNot(size_t regX, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs bitwise OR on the given registers
     * @param regX
     * @param regY
     * @param regZ
     * @param crossbars
     * @param rows
     */
    void bitwiseOr(size_t regX, size_t regY, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs bitwise AND on the given registers
     * @param regX
     * @param regY
     * @param regZ
     * @param crossbars
     * @param rows
     */
    void bitwiseAnd(size_t regX, size_t regY, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs bitwise XOR on the given registers
     * @param regX
     * @param regY
     * @param regZ
     * @param crossbars
     * @param rows
     */
    void bitwiseXor(size_t regX, size_t regY, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Performs copy on the given registers
     * @param regX
     * @param regZ
     * @param crossbars
     * @param rows
     */
    void copy(size_t regX, size_t regZ, RangeMask crossbars, RangeMask rows);

    /**
     * Intra-warp warp-parallel NOT move
     * @param inputRow
     * @param outputRow
     * @param reg
     * @param crossbars
     */
    void warpMove(size_t inputRow, size_t outputRow, size_t reg, RangeMask crossbars);

    /**
     * Returns the number of threads in a warp
     * @return
     */
    size_t warpSize();

}

#endif // CUDAPIM_DRIVER_H
