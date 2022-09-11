#pragma once
#include <cstdint>

enum ActivationFunc {
    NO_ACTIVATION_FUNCTION,
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

    NeuralNetwork(Layer* model, int numLayers, int method);
    ~NeuralNetwork();

    void operator=(const NeuralNetwork& other);
    float* getInputs();
    float* getOutputs();
    void predict();
    void print();

    double fitness;

    float* weights;
    float* biases;
    int numWeights;
    int numBiases;
    Layer* model;
    int numLayers;
    
private:

    // Weight initialization methods
    void initializeWeights(int method);
    void initializeWeightsRandomly();

    void activateLayer(int offset, int numNodes, int func, float* realTimeData);

    int numInputs;
    int numOutputs;
    float* realTimeData;

};