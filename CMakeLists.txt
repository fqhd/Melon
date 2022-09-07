cmake_minimum_required(VERSION 3.23.2)
project(Melon VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Melon SHARED src/NeuralNetwork.cpp src/Random.cpp src/Selection.cpp src/GeneticAlgorithm.cpp src/Crossover.cpp src/Mutation.cpp)

target_include_directories(Melon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(out main.cpp)

target_link_libraries(out PRIVATE Melon)