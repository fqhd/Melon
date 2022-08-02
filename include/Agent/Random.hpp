#pragma once
#include <random>

class Random{
public:
    Random();
    float get(float min, float max);

private:

    std::mt19937 generator;
    std::uniform_real_distribution<float> number;

};