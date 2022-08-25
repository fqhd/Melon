#pragma once
#include <random>
#include <ctime>

class Random{
public:

    static void seed(uint32_t seed);
    static float randomFloat(float min, float max);
    static double randomDouble(double min, double max);
    static int randomInt(int min, int max);

private:

    static std::mt19937 generator;

};