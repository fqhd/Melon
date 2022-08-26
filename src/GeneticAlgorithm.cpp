#include <Melon/GeneticAlgorithm.hpp>
#include <cstdlib>
#include <cstring>
#include <iostream>

void GeneticAlgorithm::create(Layer* m, int n, int nb){
    model = (Layer*)malloc(sizeof(Layer) * n);
    numLayers = n;
    memcpy(model, m, sizeof(Layer) * n);

    numInputs = m[0].numNodes;
    numOutputs = m[numLayers - 1].numNodes;

    int offset = 0;

    numWeights = 0;
    for(int i = 1; i < numLayers; i++){
        numWeights += model[i - 1].numNodes * model[i].numNodes;
    }
    offset += sizeof(float) * numWeights;

    numBiases = 0;
    for(int i = 1; i < numLayers; i++){
        numBiases += model[i].numNodes;
    }
    bOffset = offset;
    offset += sizeof(float) * numBiases;

    brainSize = offset;

    offset *= nb;

    int numNodes = 0;
    for(int i = 0; i < numLayers; i++){
        numNodes += m[i].numNodes;
    }
    rOffset = offset;
    offset += sizeof(float) * numNodes;

    oOffset = offset;
    offset += numOutputs * sizeof(float) * nb;

    iOffset = offset;
    offset += numInputs * sizeof(float) * nb;

    fOffset = offset;
    offset += numBrains * sizeof(float);

    data = (uint8_t*)malloc(offset);

    brains.resize(nb);
    for(int i = 0; i < brains.size(); i++){
        brains[i].init(getBrainWeights(i), getBrainBiases(i), RANDOM_WEIGHT_INITIALIZATION, numWeights, numBiases);
    }
}

void GeneticAlgorithm::setBrainInput(int brainIndex, float* data){
    memcpy(getBrainInput(brainIndex), data, sizeof(float) * numInputs);
}

float* GeneticAlgorithm::getBrainWeights(int brainIndex){
    return (float*)(data + (brainSize * brainIndex));
}

float* GeneticAlgorithm::getBrainBiases(int brainIndex){
    return (float*)(data + (brainSize * brainIndex) + bOffset);
}

float* GeneticAlgorithm::getRealTimeData(){
    return (float*)(data + rOffset);
}

void GeneticAlgorithm::feedForward(){
    for(int i = 0; i < brains.size(); i++){
        float* brainInputs = getBrainInput(i);
        float* realTimeData = getRealTimeData();
        memcpy(realTimeData, brainInputs, sizeof(float) * numInputs);
        float* output = brains[i].predict(realTimeData, model, numLayers);
        memcpy(getBrainOutput(i), output, sizeof(float) * numOutputs);
    }
}

float* GeneticAlgorithm::getBrainInput(int brainIndex){
    return (float*)(data + iOffset) + (sizeof(float) * numInputs * brainIndex);
}

float* GeneticAlgorithm::getBrainOutput(int brainIndex){
    return (float*)(data + oOffset) + (sizeof(float) * numOutputs * brainIndex);
}

void GeneticAlgorithm::setBrainFitness(int brainIndex, double fitness){
    brains[brainIndex].fitness = fitness;
}

void GeneticAlgorithm::performGeneticAlgorithm(){

}

void GeneticAlgorithm::destroy(){
    free(model);
    free(data);
}
