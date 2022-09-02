#pragma once
#include <cstdint>
#include <vector>
#include <Melon/NeuralNetwork.hpp>
#include <Melon/Selection.hpp>

class GeneticAlgorithm {
public:

    void create(Layer* model, int numLayers, int populationCount);
    void feedForward();
    float* getBrainInputs(int brainIndex);
    float* getBrainOutputs(int brainIndex);
    void performGeneticAlgorithm();
    void destroy();

private:

    float* getBrainBiases(int brainIndex);
    float* getBrainWeights(int brainIndex);
    float* getRealTimeData();

    Selection selection;
    
    Layer* model;
    int numInputs;
    int numOutputs;
    int numLayers;
    int numWeights;
    int numBiases;
    int bOffset;
    int rOffset;
    int oOffset;
    int iOffset;
    int fOffset;
    int numBrains;
    int brainSize;
    uint8_t* data;
    std::vector<NeuralNetwork> brains;

};