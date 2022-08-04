cmake_minimum_required(VERSION 3.23.2)
project(Agent VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Agent SHARED src/NeuralNetwork.cpp)

target_include_directories(Agent PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
