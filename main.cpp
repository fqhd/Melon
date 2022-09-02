#include <Melon/Random.hpp>
#include <Melon/GeneticAlgorithm.hpp>
#include <iostream>
#include <chrono>

int main(){
    Random::seed(time(0));
    Layer model[] = {
        {
            .activationFunc = NONE,
            .numNodes = 2
        },
        {
            .activationFunc = SIGMOID,
            .numNodes = 10
        },
        {
            .activationFunc = RELU,
            .numNodes = 20
        },
        {
            .activationFunc = SIGMOID,
            .numNodes = 10
        },
        {
            .activationFunc = SOFTMAX,
            .numNodes = 5
        }
    };

    GeneticAlgorithm algo;
    algo.create(model, 5, 1000);

    for(int i = 0; i < 1000; i++){
        float* inputs = algo.getBrainInputs(i);
        inputs[0] = -1.0f;
        inputs[1] = 1.0f;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 100; i++){
        algo.feedForward();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> diff = end - start;

    std::cout << diff.count() << " seconds" << std::endl;

    algo.destroy();

    return 0;
}