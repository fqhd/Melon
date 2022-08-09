#pragma once
#include <random>
#include <ctime>

class Random{
public:

    static void seed(uint32_t seed);
    static float randomFloat(float min, float max);
    static double randomDouble(double min, double max);

private:

    static std::mt19937 generator;

};