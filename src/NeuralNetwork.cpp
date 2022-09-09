#include <Melon/NeuralNetwork.hpp>
#include <cmath>
#include <iostream>
#include <Melon/Random.hpp>
#include <iostream>

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

NeuralNetwork::NeuralNetwork(Layer* m, int n, int mthd) {
    model = new Layer[n];
    numLayers = n;
    for(int i = 0; i < numLayers; i++){
        model[i] = m[i];
    }

    numInputs = m[0].numNodes;
    numOutputs = m[numLayers - 1].numNodes;

    numWeights = 0;
    for(int i = 1; i < numLayers; i++){
        numWeights += model[i - 1].numNodes * model[i].numNodes;
    }
    weights = new float[numWeights];

    numBiases = 0;
    for(int i = 1; i < numLayers; i++){
        numBiases += model[i].numNodes;
    }
    biases = new float[numBiases];

    int numNodes = 0;
    for(int i = 0; i < numLayers; i++){
        numNodes += m[i].numNodes;
    }
    realTimeData = new float[numNodes];

    initializeWeights(mthd);
}

NeuralNetwork::~NeuralNetwork() {
    delete[] model;
    delete[] weights;
    delete[] biases;
    delete[] realTimeData;
}

float* NeuralNetwork::getInputs(){
    return realTimeData;
}

float* NeuralNetwork::getOutputs(){
    return realTimeData + numBiases + numInputs - numOutputs;
}

void NeuralNetwork::print(){
    std::cout << "Weights: ";
    for(int i = 0; i < numWeights; i++){
        std::cout << weights[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "Biases: ";
    for(int i = 0; i < numBiases; i++){
        std::cout << biases[i] << ", ";
    }
    std::cout << std::endl;
}

void NeuralNetwork::predict(){
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


void NeuralNetwork::initializeWeightsRandomly(){
    for(int i = 0; i < numWeights; i++){
        weights[i] = Random::randomFloat(-1.0f, 1.0f);
    }
    for(int i = 0; i < numBiases; i++){
        biases[i] = Random::randomFloat(-1.0f, 1.0f);
    }
}

void NeuralNetwork::initializeWeights(int method){
    switch(method){
    case RANDOM_WEIGHT_INITIALIZATION:
        initializeWeightsRandomly();
        break;
    default:
        initializeWeightsRandomly();
        break;
    }
}

void NeuralNetwork::operator=(const NeuralNetwork& other){
    memcpy(weights, other.weights, sizeof(other.numWeights) * sizeof(float));
    memcpy(biases, other.biases, sizeof(other.numBiases) * sizeof(float));
    fitness = other.fitness;
}