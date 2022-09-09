#include <Melon/Crossover.hpp>
#include <Melon/Random.hpp>
#include <iostream>

void onePointCrossover(const NeuralNetwork* parent1, const NeuralNetwork* parent2, NeuralNetwork* child){
    int randomWeightPoint = Random::randomInt(0, child->numWeights);
    memcpy(child->weights, parent1->weights, sizeof(float) * randomWeightPoint);
    int diff = parent1->numWeights - randomWeightPoint;
    if(diff){
        memcpy(child->weights + randomWeightPoint, parent2->weights + randomWeightPoint, sizeof(float) * diff);
    }

    int randomBiasPoint = Random::randomInt(0, child->numBiases);
    memcpy(child->biases, parent1->biases, sizeof(float) * randomBiasPoint);
    diff = parent1->numBiases - randomBiasPoint;
    if(diff){
        memcpy(child->biases + randomBiasPoint, parent2->biases + randomBiasPoint, sizeof(float) * diff);
    }
}

void uniformCrossover(const NeuralNetwork* parent1, const NeuralNetwork* parent2, NeuralNetwork* child){
    for(int i = 0; i < child->numWeights; i++){
        child->weights[i] = Random::randomInt(0, 1) ? parent1->weights[i] : parent2->weights[i];
    }
}

Crossover::Crossover(Layer* model, int numLayers, int numBrains, int method){
    for(int i = 0; i < numBrains; i++){
        children.push_back(new NeuralNetwork(model, numLayers, RANDOM_WEIGHT_INITIALIZATION));
    }
    switch(method){
        case ONE_POINT_CROSSOVER:
            crossoverFunc = onePointCrossover;
        break;
        case UNIFORM_CROSSOVER:
            crossoverFunc = uniformCrossover;
        break;
        default:
            crossoverFunc = uniformCrossover;
        break;
    };
}

Crossover::~Crossover(){
    for(int i = 0; i < children.size(); i++){
        delete children[i];
    }
}

std::vector<NeuralNetwork*> Crossover::performCrossover(const std::vector<NeuralNetwork*>& parents){
    int index = 0;
    for(int i = 0; i < children.size(); i++){
        int p1 = index;
        int p2 = index+1;
        crossoverFunc(parents[p1], parents[p2], children[i]);
        index += 2;
    }

    return children;
}

