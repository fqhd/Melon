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
            .numNodes = 3
        },
        {
            .activationFunc = SOFTMAX,
            .numNodes = 1
        }
    };

    GeneticAlgorithm algo;
    algo.init(model, 3, 200);

    for(int i = 0; i < 200; i++){
        float* inputs = algo.getBrainInputs(i);
        inputs[0] = -1.0f;
        inputs[1] = 1.0f;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10000; i++){
        algo.feedForward();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> diff = end - start;

    for(int i = 0; i < 200; i++){
        algo.setBrainFitness(i, Random::randomDouble(0.0, 1000.0));
    }

    algo.performGeneticAlgorithm();

    std::cout << diff.count() << " seconds" << std::endl;

    return 0;
}