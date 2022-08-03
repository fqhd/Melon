#pragma once
#include <random>

class Random{
public:
    Random();
    float get();

private:

    std::mt19937 generator;
    std::uniform_real_distribution<float> number;


};