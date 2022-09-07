#include <Melon/Mutation.hpp>
#include <Melon/Random.hpp>

void randomResetting(NeuralNetwork* brain){
    brain->weights[Random::randomInt(0, brain->numWeights - 1)] = Random::randomFloat(0.0f, 1.0f);
    brain->biases[Random::randomInt(0, brain->numBiases - 1)] = Random::randomFloat(0.0f, 1.0f);
}

Mutation::Mutation(int method){
    switch(method){
        case RANDOM_RESETTING:
            mutateBrain = randomResetting;
        break;
        default:
            mutateBrain = randomResetting;
        break;
    }
}

void Mutation::performMutation(const std::vector<NeuralNetwork*>& brains){
    for(unsigned int i = 0; i < brains.size(); i++){
        randomResetting(brains[i]);
    }
}
