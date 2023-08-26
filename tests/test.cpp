
#include <iostream>
#include <cassert>
#include "../pim/vector.h"

constexpr long NUM_ITERATIONS = 64 * 1024;

int randInt(){
    return rand();
}
float randFloat(){
    return (float(rand()) / float(RAND_MAX)) - 0.5f;
}

void testIntegerAddition(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt(); y[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = x + y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] + y[i]));
    }

    std::cout << "Passed testIntegerAddition!" << std::endl;

}

void testIntegerNegation(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = -x;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (-x[i]));
    }

    std::cout << "Passed testIntegerNegation!" << std::endl;

}

void testIntegerAbs(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = x.abs();

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == std::abs(x[i]));
    }

    std::cout << "Passed testIntegerAbs!" << std::endl;

}

void testIntegerSubtraction(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt(); y[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = x - y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] - y[i]));
    }

    std::cout << "Passed testIntegerSubtraction!" << std::endl;

}

void testIntegerMultiplication(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt(); y[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = x * y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] * y[i]));
    }

    std::cout << "Passed testIntegerMultiplication!" << std::endl;

}

void testIntegerDivision(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt(); y[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = x / y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] / y[i]));
    }

    std::cout << "Passed testIntegerDivision!" << std::endl;

}

void testIntegerModulo(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt(); y[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = x % y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] % y[i]));
    }

    std::cout << "Passed testIntegerModulo!" << std::endl;

}

void testFloatingAddition(){

    // Initialize the vectors
    pim::vector<float> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randFloat(); y[i] = randFloat();
    }

    // Perform the computation
    pim::vector<float> z = x + y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] + y[i]));
    }

    std::cout << "Passed testFloatingAddition!" << std::endl;

}

void testFloatingNegation(){

    // Initialize the vectors
    pim::vector<float> x(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randFloat();
    }

    // Perform the computation
    pim::vector<float> z = -x;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (-x[i]));
    }

    std::cout << "Passed testFloatingNegation!" << std::endl;

}

void testFloatingAbs(){

    // Initialize the vectors
    pim::vector<float> x(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randFloat();
    }

    // Perform the computation
    pim::vector<float> z = x.abs();

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == std::abs(x[i]));
    }

    std::cout << "Passed testFloatingAbs!" << std::endl;

}

void testFloatingSubtraction(){

    // Initialize the vectors
    pim::vector<float> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randFloat(); y[i] = randFloat();
    }

    // Perform the computation
    pim::vector<float> z = x - y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] - y[i]));
    }

    std::cout << "Passed testFloatingSubtraction!" << std::endl;

}

void testFloatingMultiplication(){

    // Initialize the vectors
    pim::vector<float> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randFloat(); y[i] = randFloat();
    }

    // Perform the computation
    pim::vector<float> z = x * y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] * y[i]));
    }

    std::cout << "Passed testFloatingMultiplication!" << std::endl;

}

void testFloatingDivision(){

    // Initialize the vectors
    pim::vector<float> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randFloat(); y[i] = randFloat();
    }

    // Perform the computation
    pim::vector<float> z = x / y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] / y[i]));
    }

    std::cout << "Passed testFloatingDivision!" << std::endl;

}

void testBitwiseNOT(){

    // Initialize the vector
    pim::vector<int> x(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = ~x;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (~x[i]));
    }

    std::cout << "Passed testBitwiseNOT!" << std::endl;

}

void testBitwiseOR(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt(); y[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = x | y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] | y[i]));
    }

    std::cout << "Passed testBitwiseOR!" << std::endl;

}

void testBitwiseAND(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt(); y[i] = randInt();
    }

    // Perform the computation
    pim::vector<int> z = x & y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] & y[i]));
    }

    std::cout << "Passed testBitwiseAND!" << std::endl;

}

void testBitwiseXOR(){

    // Initialize the vectors
    pim::vector<int> x(NUM_ITERATIONS), y(NUM_ITERATIONS);
    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = randInt() % 1000; y[i] = randInt() % 1000;
    }

    // Perform the computation
    pim::vector<int> z = x ^ y;

    // Verify the results
    for(int i = 0; i < NUM_ITERATIONS; i++){
        assert(z[i] == (x[i] ^ y[i]));
    }

    std::cout << "Passed testBitwiseXOR!" << std::endl;

}

void (*tests[])() = {

        testIntegerAddition,
        testIntegerNegation,
        testIntegerAbs,
        testIntegerSubtraction,
        testIntegerMultiplication,
        testIntegerDivision,
        testIntegerModulo,

        testFloatingAddition,
        testFloatingNegation,
        testFloatingAbs,
        testFloatingSubtraction,
        testFloatingMultiplication,
        testFloatingDivision,

        testBitwiseNOT,
        testBitwiseOR,
        testBitwiseAND,
        testBitwiseXOR,

};

int main(){

    std::cout << "Starting Tests" << std::endl << std::endl;

    for(auto test : tests) test();

    std::cout << std::endl << "Passed All Tests!" << std::endl;

}