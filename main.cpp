#include <Melon/Random.hpp>
#include <Melon/NeuralNetwork.hpp>
#include <iostream>

int main(){
    Random::seed(time(0));
    Layer model[] = {
        {
            .activationFunc = RELU,
            .numNodes = 3
        },
        {
            .activationFunc = RELU,
            .numNodes = 5
        },
        {
            .activationFunc = SIGMOID,
            .numNodes = 2
        }
    };

    NeuralNetwork nn;
    nn.loadFromFile("nn.bin");

    float data[] = {0.6, 0.9, 0.1};
    float* outputs = nn.predict(data, 3);
    std::cout << outputs[0] << std::endl;
    std::cout << outputs[1] << std::endl;
    
    // nn.save("nn.bin");

    return 0;
}