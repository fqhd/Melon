#include <Agent/NeuralNetwork.hpp>
#include <iostream>

NeuralNetwork::NeuralNetwork(int* m, int n){
    model = m; // TODO: fix this memory leak
    numLayers = n;
    numInputs = m[0];
    numOutputs = m[n - 1];

    int numWeights = 0;
    for(int i = 1; i < numLayers; i++){
        numWeights += m[i - 1] * m[i];
    }
    weights = (float*)malloc(sizeof(float) * numWeights);

    int numBiases = 0;
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

NeuralNetwork::~NeuralNetwork(){
    free(weights);
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
            float bias = biases[biasIndex];
            biasIndex++;
            for(int k = 0; k < numWeightsInNode; k++){ // Loop through each weight
                float weight = weights[weightIndex];
                weightIndex++;
                result += weight * realtimeData[layerOffset + k];
            }
            result += bias;
            realtimeData[layerOffset + model[i - 1] + j] = result;
        }
        layerOffset += model[i - 1];
    }

    return realtimeData + layerOffset;
}

