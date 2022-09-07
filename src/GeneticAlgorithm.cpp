#include <Melon/GeneticAlgorithm.hpp>
#include <cstdlib>
#include <cstring>
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(Layer *model, int numLayers, int numBrains) : selection(numBrains, ROULETTE_SELECTION), crossover(model, numLayers, numBrains, ONE_POINT_CROSSOVER), mutation(RANDOM_RESETTING)
{
    for (int i = 0; i < numBrains; i++)
    {
        brains.push_back(new NeuralNetwork(model, numLayers, RANDOM_WEIGHT_INITIALIZATION));
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

    // TODO: Copy childrens array into brains array

    parents[0]->print();
    parents[1]->print();
    children[0]->print();
}

void GeneticAlgorithm::setBrainFitness(int index, double fitness){
    brains[index]->fitness = fitness;
}