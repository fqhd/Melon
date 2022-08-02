#pragma once
#include <array>

class NeuralNetwork {
public:
    NeuralNetwork(int* model, int numLayers);
    ~NeuralNetwork();

private:
    float* weights;
    int* model;
    int numLayers;
};