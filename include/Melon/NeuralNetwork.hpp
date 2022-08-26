#pragma once
#include <cstdint>

enum ActivationFunc {
    NONE,
    SIGMOID,
    RELU,
    SOFTMAX,
    LEAKY_RELU,
    TANH
};

enum WeightInitializationMethod {
    RANDOM_WEIGHT_INITIALIZATION
};

struct Layer {
    int activationFunc;
    int numNodes;
};

class NeuralNetwork {
public:

    void init(float* weights, float* biases, int method, int numWeights, int numBiases);
    float* predict(float* realTimeData, Layer* model, int numLayers);

    double fitness;

private:

    // Weight initialization methods
    void initializeWeights(int method, int numWeights, int numBiases);
    void initializeWeightsRandomly(int numWeights, int numBiases);

    void activateLayer(int offset, int numNodes, int func, float* realTimeData);

    float* weights;
    float* biases;

};