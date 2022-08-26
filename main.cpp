#include <Melon/Random.hpp>
#include <Melon/GeneticAlgorithm.hpp>
#include <iostream>

int main(){
    Random::seed(time(0));
    Layer model[] = {
        {
            .activationFunc = NONE,
            .numNodes = 2
        },
        {
            .activationFunc = NONE,
            .numNodes = 3
        },
        {
            .activationFunc = NONE,
            .numNodes = 1
        }
    };

    GeneticAlgorithm algo;
    algo.create(model, 3, 1);

    float input[] = {
        -1.0f, 1.0f
    };

    algo.setBrainInput(0, input);

    algo.feedForward();

    float* outputs = algo.getBrainOutput(0);
    std::cout << outputs[0] << std::endl;

    algo.destroy();

    return 0;
}