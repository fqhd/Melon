#pragma once
#include <array>

class NeuralNetwork {
public:
    NeuralNetwork(const char* path);
    NeuralNetwork(int* model, int numLayers);
    ~NeuralNetwork();
    float* predict(float* inputs, int numInputs);
    int getNumOutputs();
    int getNumInputs();
    int getNumWeights();
    int getNumBiases();
    void save(const char* path);

    float* weights;
    float* biases;

private:

    void init();

    float* realtimeData; // This is used internally to feed forward the network.
    int* model;
    int numWeights;
    int numBiases;
    int numLayers;
    int numOutputs;
    int numInputs;

};