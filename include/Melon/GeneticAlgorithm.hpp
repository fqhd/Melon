#pragma once
#include <cstdint>
#include <vector>
#include <Melon/NeuralNetwork.hpp>
#include <Melon/Selection.hpp>
#include <Melon/Crossover.hpp>

class GeneticAlgorithm {
public:

    GeneticAlgorithm(Layer* model, int numLayers, int populationCount);
    void feedForward();
    float* getBrainInputs(int brainIndex);
    float* getBrainOutputs(int brainIndex);
    void performGeneticAlgorithm();

private:

    Selection selection;
    Crossover crossover;
    std::vector<NeuralNetwork*> brains;   

};