#include <Melon/Random.hpp>
#include <Melon/GeneticAlgorithm.hpp>
#include <iostream>
#include <chrono>

int main(){
    Random::seed(time(0));
    Layer model[] = {
        {
            .activationFunc = NO_ACTIVATION_FUNCTION,
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

    GeneticAlgorithm algo(model, 5, 200);

    for(int i = 0; i < 200; i++){
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

    algo.performGeneticAlgorithm();

    std::cout << diff.count() << " seconds" << std::endl;

    return 0;
}