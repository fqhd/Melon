#include <Melon/Random.hpp>
#include <Melon/NeuralNetwork.hpp>
#include <Melon/Selection.hpp>
#include <iostream>

int main(){
    Random::seed(time(0));
    Layer model[] = {
        {
            .activationFunc = LEAKY_RELU,
            .numNodes = 3
        },
        {
            .activationFunc = LEAKY_RELU,
            .numNodes = 5
        },
        {
            .activationFunc = SIGMOID,
            .numNodes = 2
        }
    };

    NeuralNetwork* brains = (NeuralNetwork*)malloc(sizeof(NeuralNetwork) * 300);
    for(int i = 0; i < 300; i++){
        brains[i].create(model, 3, RANDOM_WEIGHT_INITIALIZATION);
    }

    for(int i = 0; i < 300; i++){
        brains[i].fitness = 0.0f;
    }

    brains[10].fitness = 1.0;
    brains[5].fitness = 0.5;

    Selection selection;
    selection.init(300, ROULETTE);

    int* parents = selection.performSelection(brains);

    for(int i = 0; i < 600; i++){
        std::cout << parents[i] << std::endl;
    }

    selection.destroy();

    for(int i = 0; i < 300; i++){
        brains[i].destroy();
    }
    
    return 0;
}