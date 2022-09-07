#include <Melon/Mutation.hpp>
#include <Melon/Random.hpp>

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

void scrambleMutation(NeuralNetwork* brain){

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
