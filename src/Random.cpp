#include <Agent/Random.hpp>

Random::Random(){
    generator.seed(5);
}

float Random::randomFloat(float min, float max){
    std::uniform_real_distribution<float> number(min, max);
    return number(generator);
}

double Random::randomDouble(double min, double max){
    std::uniform_real_distribution<double> number(min, max);
    return number(generator);
}