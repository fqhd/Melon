#include <Agent/NeuralNetwork.hpp>
#include <iostream>

NeuralNetwork::NeuralNetwork(int* m, int n){
    model = m;
    numLayers = n;

    uint32_t numWeights = 0;
    for(int i = 1; i < numLayers; i++){
        numWeights += m[i - 1] * m[i];
    }

    weights = (float*)malloc(sizeof(float) * numWeights);
}

NeuralNetwork::~NeuralNetwork(){
    free(weights);
}