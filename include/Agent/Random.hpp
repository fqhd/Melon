#pragma once
#include <random>

class Random{
public:
    Random();
    float randomFloat(float min, float max);
    double randomDouble(double min, double max);

private:

    std::mt19937 generator;

};