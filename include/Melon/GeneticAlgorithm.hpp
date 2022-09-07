#pragma once
#include <cstdint>
#include <vector>
#include <Melon/NeuralNetwork.hpp>
#include <Melon/Selection.hpp>
#include <Melon/Crossover.hpp>
#include <Melon/Mutation.hpp>

class GeneticAlgorithm {
public:

    GeneticAlgorithm(Layer* model, int numLayers, int populationCount);
    void feedForward();
    float* getBrainInputs(int brainIndex);
    float* getBrainOutputs(int brainIndex);
    void performGeneticAlgorithm();
    void setBrainFitness(int index, double fitness);

private:

    Selection selection;
    Crossover crossover;
    Mutation mutation;
    std::vector<NeuralNetwork*> brains;   

};