cmake_minimum_required(VERSION 3.23.2)
project(Agent VERSION 1.0.0)

add_library(Agent SHARED src/NeuralNetwork.cpp src/Random.cpp)

target_include_directories(Agent PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(out main.cpp)

target_link_libraries(out PRIVATE Agent)