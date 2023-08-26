cmake_minimum_required(VERSION 3.19)
project(CUDAPIM)

find_package(CUDA REQUIRED)
enable_language(CUDA)

# Set compiler optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

cuda_add_library(simulator STATIC pim/simulator.cuh pim/simulator.cu pim/constants.h)
add_library(dev STATIC pim/vector.h pim/memory.cpp pim/memory.h pim/constants.h pim/algorithm.h)
add_library(driver STATIC pim/driver.h pim/driver.cpp pim/constants.h)

add_executable(main main.cpp)
target_link_libraries(main dev driver simulator)

add_executable(matrix tests/matrix.cpp)
target_link_libraries(matrix dev driver simulator)

add_executable(fft tests/fft.cpp)
target_link_libraries(fft dev driver simulator)

add_executable(test tests/test.cpp)
target_link_libraries(test dev driver simulator)

set(CMAKE_CXX_STANDARD 17)