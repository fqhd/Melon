#include <Melon/Mutation.hpp>
#include <Melon/Random.hpp>
#include <math.h>
#include <iostream>


void Mutation::randomResetting(NeuralNetwork* brain){
    for(int i = 0; i < brain->numWeights; i++){
        if(Random::randomDouble(0.0, 1.0) <= weightMutationChance){
            brain->weights[i] = Random::randomFloat(0.0f, 1.0f);
        }
    }

    for(int i = 0; i < brain->numBiases; i++){
        if(Random::randomDouble(0.0, 1.0) <= biasMutationChance){
            brain->biases[i] = Random::randomFloat(0.0f, 1.0f);
        }
    }
}

void Mutation::nudgeMutation(NeuralNetwork* brain){
    for(int i = 0; i < brain->numWeights; i++){
        if(Random::randomDouble(0.0, 1.0) <= weightMutationChance){
            brain->weights[i] += Random::randomFloat(-nudgeAmount, nudgeAmount);
        }
    }

    for(int i = 0; i < brain->numBiases; i++){
        if(Random::randomDouble(0.0, 1.0) <= biasMutationChance){
            brain->biases[i] += Random::randomFloat(-nudgeAmount, nudgeAmount);
        }
    }
}

void shuffle(float* array, int size){
    int m = size;
    float t = 0;
    int i = 0;

    while(m){
        i = floor(Random::randomFloat(0.0f, 0.999f) * m--);
        t = array[m];
        array[m] = array[i];
        array[i] = t;
    }
}

void Mutation::scrambleMutation(NeuralNetwork* brain){
    float chunkCut = 0.5; // Chunk that will be scrambled is 50% of the weights
    int weightChunkSize = (brain->numWeights * chunkCut);

    if(weightChunkSize != 0){
        int chunkPos = Random::randomInt(0, brain->numWeights - weightChunkSize - 1);
        shuffle(brain->weights + chunkPos, weightChunkSize);
    }

    int biasChunkSize = (brain->numBiases * chunkCut);

    if(biasChunkSize != 0){
        int chunkPos = Random::randomInt(0, brain->numBiases - biasChunkSize - 1);
        shuffle(brain->biases + chunkPos, biasChunkSize);
    }
}

void Mutation::performMutation(const std::vector<NeuralNetwork*>& brains){
    switch(method){
        case RANDOM_RESETTING:
            for(unsigned int i = 0; i < brains.size(); i++){
                randomResetting(brains[i]);
            }
        break;
        case SCRAMBLE_MUTATION:
            for(unsigned int i = 0; i < brains.size(); i++){
                scrambleMutation(brains[i]);
            }
        break;
        case NUDGE_MUTATION:
            for(unsigned int i = 0; i < brains.size(); i++){
                nudgeMutation(brains[i]);
            }
        break;
    }
}
