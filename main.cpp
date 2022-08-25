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

    std::vector<NeuralNetwork> brains;
    brains.resize(300);

    for(int i = 0; i < brains.size(); i++){
        brains[i].create(model, 3, RANDOM_WEIGHT_INITIALIZATION);
    }

    for(int i = 0; i < brains.size(); i++){
        brains[i].fitness = 0.0f;
    }

    brains[10].fitness = 1.0;
    brains[5].fitness = 0.5;

    Selection selection;
    selection.init(brains.size(), RANK);

    int* parents = selection.performSelection(brains);

    int num = 0;
    for(int i = 0; i < brains.size() * 2; i++){
        std::cout << parents[i] << std::endl;
        if(parents[i] == 10){
            num++;
        }
    }

    std::cout << "N: " << num / (brains.size() * 2.0f) << std::endl;


    // Clean Up
    selection.destroy();
    for(int i = 0; i < brains.size(); i++){
        brains[i].destroy();
    }
    return 0;
}