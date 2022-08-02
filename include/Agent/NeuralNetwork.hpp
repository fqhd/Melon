#pragma once
#include <array>

class NeuralNetwork {
public:
    NeuralNetwork(int* model, int numLayers);
    ~NeuralNetwork();
    float* predict(float* inputs, int numInputs);
    int getNumOutputs();
    int getNumInputs();

private:
    float* realtimeData; // This is used to internally feed forward the network.
    float* weights;
    float* biases;
    int* model;
    int numLayers;
    int numOutputs;
    int numInputs;
};