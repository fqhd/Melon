#include <Agent/Random.hpp>

Random::Random():number(-1.0f, 1.0f){
    generator.seed(time(0));
}

float Random::get(){
    return number(generator);
}