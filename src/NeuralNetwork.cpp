#include <Melon/NeuralNetwork.hpp>
#include <cmath>
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

NeuralNetwork::NeuralNetwork(Layer* m, int n) {
    model = (Layer*)malloc(sizeof(Layer) * n);
    memcpy(model, m, sizeof(Layer) * n);
    numLayers = n;
    init();
}

NeuralNetwork::NeuralNetwork(const char* path){
    FILE* ourFile = fopen(path, "rb");
    if(ourFile == NULL){
        std::cout << "Failed to open file" << std::endl;
    }
    
    fread(&numLayers, sizeof(int), 1, ourFile);
    model = (Layer*)malloc(sizeof(Layer) * numLayers);
    fread(model, sizeof(Layer) * numLayers, 1, ourFile);
    init();
    fread(weights, sizeof(float) * numWeights, 1, ourFile);
    fread(biases, sizeof(float) * numBiases, 1, ourFile);
    fclose(ourFile);
}

void NeuralNetwork::init(){
    numInputs = model[0].numNodes;
    numOutputs = model[numLayers - 1].numNodes;

    numWeights = 0;
    for(int i = 1; i < numLayers; i++){
        numWeights += model[i - 1].numNodes * model[i].numNodes;
    }
    weights = (float*)malloc(sizeof(float) * numWeights);

    numBiases = 0;
    for(int i = 1; i < numLayers; i++){
        numBiases += model[i].numNodes;
    }
    biases = (float*)malloc(sizeof(float) * numBiases);

    int numNodes = 0;
    for(int i = 0; i < numLayers; i++){
        numNodes += model[i].numNodes;
    }
    realtimeData = (float*)malloc(sizeof(float) * numNodes);
}

int NeuralNetwork::getNumWeights(){
    return numWeights;
}

int NeuralNetwork::getNumBiases(){
    return numBiases;
}

NeuralNetwork::~NeuralNetwork(){
    free(weights);
    free(model);
    free(biases);
    free(realtimeData);
}

int NeuralNetwork::getNumOutputs(){
    return numOutputs;
}

int NeuralNetwork::getNumInputs(){
    return numInputs;
}

void NeuralNetwork::save(const char* path){
    FILE* ourFile = fopen(path, "wb");

    fwrite(&numLayers, sizeof(numLayers), 1, ourFile);
    fwrite(model, sizeof(Layer) * numLayers, 1, ourFile);
    fwrite(weights, sizeof(float) * numWeights, 1, ourFile);
    fwrite(biases, sizeof(float) * numBiases, 1, ourFile);

    fclose(ourFile);
}

float* NeuralNetwork::predict(float* inputs, int n){
    if(n != numInputs){
        std::cout << "Wrong number of inputs passed into neural network!" << std::endl;
        return nullptr;
    }

    // Copy input data into tempData
    memcpy(realtimeData, inputs, sizeof(float) * numInputs);

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
                result += weight * realtimeData[layerOffset + k];
            }
            result += bias;
            realtimeData[layerOffset + model[i - 1].numNodes + j] = result;
        }
        activateLayer(layerOffset + model[i - 1].numNodes, numNodesInLayer, model[i].activationFunc);
        layerOffset += model[i - 1].numNodes;
    }

    return realtimeData + layerOffset;
}

void NeuralNetwork::activateLayer(int offset, int numNodes, int func){
    switch (func) {
        case RELU:
            for(int i = 0; i < numNodes; i++){
                float x = realtimeData[offset + i];
                realtimeData[offset + i] = relu(x);
            }
            break;

        case LEAKY_RELU:
            for(int i = 0; i < numNodes; i++){
                float x = realtimeData[offset + i];
                realtimeData[offset + i] = lrelu(x);
            }
            break;

        case TANH:
            for(int i = 0; i < numNodes; i++){
                float x = realtimeData[offset + i];
                realtimeData[offset + i] = tanh(x);
            }
            break;

        case SOFTMAX:
            softmax(realtimeData + offset, numNodes);
            break;
    
        default:
            for(int i = 0; i < numNodes; i++){
                float x = realtimeData[offset + i];
                realtimeData[offset + i] = sigmoid(x);
            }
            break;
    }
}
