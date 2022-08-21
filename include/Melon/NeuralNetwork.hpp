#pragma once
#include <cstdint>

enum ActivationFunc {
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

    void create(Layer* model, int numLayers, int method);
    void loadFromFile(const char* path);
    float* predict(float* inputs, int numInputs);
    void save(const char* path);
    void destroy();

    int getNumOutputs();
    int getNumInputs();
    int getNumWeights();
    int getNumBiases();
    float* getWeights();
    float* getBiases();

    double fitness;

private:

    // Weight initialization methods
    void initializeWeights(int method);
    void initializeWeightsRandomly();

    void activateLayer(int offset, int numNodes, int func);
    float* getRealTimeData();
    Layer* getModel();

    uint8_t* data;

    int dataSize;
    int wOffset;
    int bOffset;
    int rtdOffset;
    int numWeights;
    int numBiases;
    int numLayers;
    int numOutputs;
    int numInputs;

};