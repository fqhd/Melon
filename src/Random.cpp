#include <Agent/Random.hpp>

Random::Random(){
    generator.seed(time(0));
}

float Random::get(float min, float max){
    std::uniform_real_distribution<float> number(min, max);
    return number(generator);
}