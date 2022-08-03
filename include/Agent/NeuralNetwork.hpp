#pragma once
#include <array>
#include <Agent/Random.hpp>

class NeuralNetwork {
public:
    NeuralNetwork(int* model, int numLayers, Random* random);
    ~NeuralNetwork();
    float* predict(float* inputs, int numInputs);
    int getNumOutputs();
    int getNumInputs();
    void mutate();

private:

    void initRandomWeightsAndBiases(int numWeights, int numBiases, Random* random);

    float* realtimeData; // This is used internally to feed forward the network.
    float* weights;
    float* biases;
    int* model;
    int numLayers;
    int numOutputs;
    int numInputs;
};