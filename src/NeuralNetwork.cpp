#include <Melon/NeuralNetwork.hpp>
#include <cmath>
#include <iostream>
#include <Melon/Random.hpp>

#define EULER_NUMBER_F 2.71828182846

float sigmoid(float x) {
    return (1 / (1 + powf(EULER_NUMBER_F, -x)));
}

float relu(float x){
    return fmax(0.0f, x);
}

float lrelu(float x){
    return fmax(0.01f * x, x);
}

void softmax(float *input, int input_len) {
    float m = -INFINITY;
    for (int i = 0; i < input_len; i++) {
        if (input[i] > m) {
            m = input[i];
        }
    }

    float sum = 0.0;
    for (int i = 0; i < input_len; i++) {
        sum += expf(input[i] - m);
    }

    float offset = m + logf(sum);
    for (int i = 0; i < input_len; i++) {
        input[i] = expf(input[i] - offset);
    }
}

void NeuralNetwork::init(float* w, float* b, int method, int numWeights, int numBiases) {
    weights = w;
    biases = b;

    initializeWeights(method, numWeights, numBiases);
}

float* NeuralNetwork::predict(float* realTimeData, Layer* model, int numLayers){
    // Copy input data into tempData
    uint32_t biasIndex = 0;
    uint32_t weightIndex = 0;
    uint32_t layerOffset = 0;
    for(int i = 1; i < numLayers; i++){
        int numNodesInLayer = model[i].numNodes;
        int numWeightsInNode = model[i - 1].numNodes;
        for(int j = 0; j < numNodesInLayer; j++){ // Loop through each node
            float result = 0.0f;
            float bias = biases[biasIndex++];
            for(int k = 0; k < numWeightsInNode; k++){ // Loop through each weight
                float weight = weights[weightIndex++];
                result += weight * realTimeData[layerOffset + k];
            }
            result += bias;
            realTimeData[layerOffset + model[i - 1].numNodes + j] = result;
        }
        activateLayer(layerOffset + model[i - 1].numNodes, numNodesInLayer, model[i].activationFunc, realTimeData);
        layerOffset += model[i - 1].numNodes;
    }
    
    return realTimeData + layerOffset;
}

void NeuralNetwork::activateLayer(int offset, int numNodes, int func, float* realTimeData){
    switch (func) {
        case RELU:
            for(int i = 0; i < numNodes; i++){
                float x = realTimeData[offset + i];
                realTimeData[offset + i] = relu(x);
            }
            break;

        case LEAKY_RELU:
            for(int i = 0; i < numNodes; i++){
                float x = realTimeData[offset + i];
                realTimeData[offset + i] = lrelu(x);
            }
            break;

        case TANH:
            for(int i = 0; i < numNodes; i++){
                float x = realTimeData[offset + i];
                realTimeData[offset + i] = tanh(x);
            }
            break;

        case SOFTMAX:
            softmax(realTimeData + offset, numNodes);
            break;
    
        default:
            break;
    }
}


void NeuralNetwork::initializeWeightsRandomly(int numWeights, int numBiases){
    for(int i = 0; i < numWeights; i++){
        weights[i] = Random::randomFloat(-1.0f, 1.0f);
    }
    for(int i = 0; i < numBiases; i++){
        biases[i] = Random::randomFloat(-1.0f, 1.0f);
    }
}

void NeuralNetwork::initializeWeights(int method, int numWeights, int numBiases){
    switch(method){
    case RANDOM_WEIGHT_INITIALIZATION:
        initializeWeightsRandomly(numWeights, numBiases);
        break;
    default:
        initializeWeightsRandomly(numWeights, numBiases);
        break;
    }
}