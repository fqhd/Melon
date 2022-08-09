#include <Melon/Random.hpp>
#include <iostream>

int main(){
    Random::seed(21);
    std::cout << Random::randomFloat(-1.0f, 1.0f) << std::endl;
    return 0;
}