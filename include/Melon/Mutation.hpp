#pragma once

#include <Melon/NeuralNetwork.hpp>
#include <vector>

enum MutationMethods {
    RANDOM_RESETTING,
    SCRAMBLE_MUTATION,
    NUDGE_MUTATION
};

class Mutation {
public:

    void performMutation(const std::vector<NeuralNetwork*>& brains);

    float weightMutationChance = 0.01;
    float biasMutationChance = 0.01;
    float nudgeAmount = 0.2;
    int method = RANDOM_RESETTING;

private:

    void scrambleMutation(NeuralNetwork* brain);
    void nudgeMutation(NeuralNetwork* brain);
    void randomResetting(NeuralNetwork* brain);

};