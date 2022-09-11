#include <Melon/GeneticAlgorithm.hpp>
#include <cstdlib>
#include <cstring>
#include <iostream>

void GeneticAlgorithm::init(Layer *model, int numLayers, int numBrains) {
    selection.init(numBrains);
    crossover.init(model, numLayers, numBrains);
    for (int i = 0; i < numBrains; i++)
    {
        brains.push_back(new NeuralNetwork(model, numLayers, RANDOM_WEIGHT_INITIALIZATION));
    }
}

GeneticAlgorithm::~GeneticAlgorithm(){
    for(int i = 0; i < brains.size(); i++){
        delete brains[i];
    }
}

void GeneticAlgorithm::feedForward()
{
    for (int i = 0; i < brains.size(); i++)
    {
        brains[i]->predict();
    }
}

float *GeneticAlgorithm::getBrainInputs(int brainIndex)
{
    return brains[brainIndex]->getInputs();
}

float *GeneticAlgorithm::getBrainOutputs(int brainIndex)
{
    return brains[brainIndex]->getOutputs();
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

void GeneticAlgorithm::setBrainFitness(int index, double fitness){
    brains[index]->fitness = fitness;
}