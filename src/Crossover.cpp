#include <Melon/Crossover.hpp>
#include <Melon/Random.hpp>
#include <iostream>

Crossover::Crossover(){
    method = AVERAGE_CROSSOVER;
}

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
    for(int i = 0; i < child->numBiases; i++){
        child->biases[i] = Random::randomInt(0, 1) ? parent1->biases[i] : parent2->biases[i];
    }
}

void averageCrossover(const NeuralNetwork* parent1, const NeuralNetwork* parent2, NeuralNetwork* child){
    for(int i = 0; i < child->numWeights; i++){
        child->weights[i] = (parent1->weights[i] + parent2->weights[i]) / 2.0f;
    }
    for(int i = 0; i < child->numBiases; i++){
        child->biases[i] = (parent1->biases[i] + parent2->biases[i]) / 2.0f;
    }
}

void Crossover::init(Layer* model, int numLayers, int numBrains){
    for(int i = 0; i < numBrains; i++){
        children.push_back(new NeuralNetwork(model, numLayers, RANDOM_WEIGHT_INITIALIZATION));
    }
}

void Crossover::destroy(){
    for(int i = 0; i < children.size(); i++){
        delete children[i];
    }
}

std::vector<NeuralNetwork*> Crossover::performCrossover(const std::vector<NeuralNetwork*>& parents){
    int index = 0;
    for(int i = 0; i < children.size(); i++){
        int p1 = index;
        int p2 = index + 1;
        switch(method){
            case ONE_POINT_CROSSOVER:
                onePointCrossover(parents[p1], parents[p2], children[i]);
            break;
            case UNIFORM_CROSSOVER:
                uniformCrossover(parents[p1], parents[p2], children[i]);
            break;
            case AVERAGE_CROSSOVER:
                averageCrossover(parents[p1], parents[p2], children[i]);
            break;
            default:
                uniformCrossover(parents[p1], parents[p2], children[i]);
            break;
        };
        index += 2;
    }
    return children;
}

