#include <Agent/NeuralNetwork.hpp>
#include <iostream>

NeuralNetwork::NeuralNetwork(int* m, int n) {
    model = (int*)malloc(sizeof(int) * n);
    memcpy(model, m, sizeof(int) * n);
    numLayers = n;
    numInputs = m[0];
    numOutputs = m[n - 1];

    numWeights = 0;
    for(int i = 1; i < numLayers; i++){
        numWeights += m[i - 1] * m[i];
    }
    weights = (float*)malloc(sizeof(float) * numWeights);

    numBiases = 0;
    for(int i = 1; i < numLayers; i++){
        numBiases += m[i];
    }
    biases = (float*)malloc(sizeof(float) * numBiases);

    int numNodes = 0;
    for(int i = 0; i < numLayers; i++){
        numNodes += m[i];
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
        int numNodesInLayer = model[i];
        int numWeightsInNode = model[i - 1];
        for(int j = 0; j < numNodesInLayer; j++){ // Loop through each node
            float result = 0.0f;
            float bias = biases[biasIndex++];
            for(int k = 0; k < numWeightsInNode; k++){ // Loop through each weight
                float weight = weights[weightIndex++];
                result += weight * realtimeData[layerOffset + k];
            }
            result += bias;
            realtimeData[layerOffset + model[i - 1] + j] = result;
        }
        layerOffset += model[i - 1];
    }

    return realtimeData + layerOffset;
}

