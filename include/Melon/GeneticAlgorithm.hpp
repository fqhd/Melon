#pragma once
#include <cstdint>
#include <vector>
#include <Melon/NeuralNetwork.hpp>

class GeneticAlgorithm {
public:

    void create(Layer* model, int numLayers, int populationCount);
    void setBrainInput(int brainIndex, float* data);
    void feedForward();
    float* getBrainOutput(int brainIndex);
    float* getBrainInput(int brainIndex);
    void setBrainFitness(int brainIndex, double fitness);
    void performGeneticAlgorithm();
    void destroy();

private:

    float* getBrainBiases(int brainIndex);
    float* getBrainWeights(int brainIndex);
    float* getRealTimeData();

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