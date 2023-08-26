#include <iostream>
#include "pim/vector.h"
#include "pim/algorithm.h"

pim::vector<float> myFunc(const pim::vector<float>& x, const pim::vector<float>& y){
    // Parallel multiplication and addition
    return x * y + x;
}

int main() {

    // Allocating and initializing vectors x and y
    pim::vector<float> x(1e6, 0), y(1e6, 0);
    x[5] = 8.0; y[5] = 0.5; x[7] = 10.0; y[7] = 1.0;

    // Function call
    pim::vector<float> z = myFunc(x, y);

    // Logarithmic-time parallel reduction
    std::cout << pim::sum<float>(z) << std::endl;

    return 0;

}