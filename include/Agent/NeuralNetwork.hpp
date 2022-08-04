#pragma once
#include <array>

#define SIGMOID 0
#define RELU 1
#define SOFTMAX 2

struct Layer {
    int activationFunc;
    int numNodes;
};

class NeuralNetwork {
public:
    NeuralNetwork(const char* path);
    NeuralNetwork(Layer* model, int numLayers);
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
    Layer* model;
    int numWeights;
    int numBiases;
    int numLayers;
    int numOutputs;
    int numInputs;

};