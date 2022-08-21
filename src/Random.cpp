#include <Melon/Random.hpp>

std::mt19937 Random::generator;

void Random::seed(uint32_t seed){
    generator.seed(seed);
}

float Random::randomFloat(float min, float max){
    std::uniform_real_distribution<float> number(min, max); // Optimize this
    return number(generator);
}

double Random::randomDouble(double min, double max){
    std::uniform_real_distribution<double> number(min, max); // Optimize this
    return number(generator);
}