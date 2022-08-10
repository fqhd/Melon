#pragma once
#include <array>

#define SIGMOID 0
#define RELU 1
#define SOFTMAX 2
#define LEAKY_RELU 3
#define TANH 4

struct Layer {
    int activationFunc;
    int numNodes;
};

class NeuralNetwork {
public:

    void create(Layer* model, int numLayers);
    void loadFromFile(const char* path);
    float* predict(float* inputs, int numInputs);
    void save(const char* path);
    void destroy();

    int getNumOutputs();
    int getNumInputs();
    int getNumWeights();
    int getNumBiases();

    float* weights;
    float* biases;
    float fitness;

private:

    void init();
    void activateLayer(int offset, int numNodes, int func);

    float* realtimeData; // This is used internally to feed forward the network.
    Layer* model;
    int numWeights;
    int numBiases;
    int numLayers;
    int numOutputs;
    int numInputs;

};