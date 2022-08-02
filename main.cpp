#include <iostream>
#include <Agent/NeuralNetwork.hpp>

int main(){
    int model[] = {3, 4, 2};
    NeuralNetwork nn(model, sizeof(model)/sizeof(model[0]));
    std::cout << "Hello, World!" << std::endl;
    return 0;
}