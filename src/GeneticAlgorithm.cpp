#include <Melon/GeneticAlgorithm.hpp>
#include <cstdlib>
#include <cstring>
#include <iostream>

void GeneticAlgorithm::init() {
    if (brains.size() == 0) {
        std::cout << "Add brains(NeuralNetworks) before initializing genetic algorithm" << std::endl;
        return;
    }
    crossover.init(brains[0]->model, brains[0]->numLayers, (int)brains.size());
}

void GeneticAlgorithm::performGeneticAlgorithm()
{
    std::vector<NeuralNetwork*> parents = selection.performSelection(brains);
    std::vector<NeuralNetwork*> children = crossover.performCrossover(parents);
    mutation.performMutation(children);

    for(int i = 0; i < children.size(); i++){
        *brains[i] = *children[i];
    }
}

void GeneticAlgorithm::destroy(){
    crossover.destroy();
}
