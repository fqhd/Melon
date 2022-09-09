#include <Melon/Mutation.hpp>
#include <Melon/Random.hpp>
#include <math.h>
#include <iostream>

void randomResetting(NeuralNetwork* brain){
    double weightMutationChance = 0.01; // 1% chance of mutation
    for(int i = 0; i < brain->numWeights; i++){
        if(Random::randomDouble(0.0, 1.0) <= weightMutationChance){
            brain->weights[i] = Random::randomFloat(0.0f, 1.0f);
        }
    }

    double biasMutationChance = 0.01; // 1% chance of mutation
    for(int i = 0; i < brain->numBiases; i++){
        if(Random::randomDouble(0.0, 1.0) <= biasMutationChance){
            brain->biases[i] = Random::randomFloat(0.0f, 1.0f);
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

void scrambleMutation(NeuralNetwork* brain){
    float chunkCut = 0.5; // Chunk that will be scrambled is 50% of the weights
    int weightChunkSize = (brain->numWeights * chunkCut);

    if(weightChunkSize != 0){
        int chunkPos = Random::randomInt(0, brain->numWeights - weightChunkSize - 1);
        shuffle(brain->weights + chunkPos, weightChunkSize);
    }
}

Mutation::Mutation(int method){
    switch(method){
        case RANDOM_RESETTING:
            mutationFunc = randomResetting;
        break;
        case SCRAMBLE_MUTATION:
            mutationFunc = scrambleMutation;
        break;
        default:
            mutationFunc = randomResetting;
        break;
    }
}

void Mutation::performMutation(const std::vector<NeuralNetwork*>& brains){
    for(unsigned int i = 0; i < brains.size(); i++){
        mutationFunc(brains[i]);
    }
}
