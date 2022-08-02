#include <iostream>
#include <Agent/NeuralNetwork.hpp>

int main(){
    int model[] = {3, 4, 2};
    NeuralNetwork nn(model, sizeof(model)/sizeof(model[0]));

    float data[] = {
        1.0f, 1.0f, 1.0f
    };
    float* output = nn.predict(data, 3);
    std::cout << output[0] << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}