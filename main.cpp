#include <iostream>
#include <Agent/NeuralNetwork.hpp>
#include <Agent/Random.hpp>
#include <chrono>

int main(){
    Layer model[] = {
        {
            .activationFunc = SIGMOID,
            .numNodes = 3
        },
        {
            .activationFunc = SIGMOID,
            .numNodes = 4
        },
        {
            .activationFunc = SIGMOID,
            .numNodes = 2
        }
    };
    Random::seed(time(0));
    NeuralNetwork nn(model, sizeof(model)/sizeof(model[0]));

    float data[] = {
        1.0f, 1.0f, 1.0f
    };

    auto start = std::chrono::high_resolution_clock::now();
    float* output = nn.predict(data, sizeof(data)/sizeof(data[0]));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << "s" << std::endl;

    std::cout << output[0] << std::endl;
    std::cout << output[1] << std::endl;
    std::cout << output[2] << std::endl;
    nn.save("nn.bin");
    return 0;
}