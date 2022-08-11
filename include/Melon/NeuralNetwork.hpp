#pragma once
#include <cstdint>

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
    float* getWeights();
    float* getBiases();

    float fitness;

private:

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