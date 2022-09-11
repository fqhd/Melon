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

    Mutation();
    void performMutation(const std::vector<NeuralNetwork*>& brains);

    float weightMutationChance;
    float biasMutationChance;
    float nudgeAmount;
    int method;

private:

    void scrambleMutation(NeuralNetwork* brain);
    void nudgeMutation(NeuralNetwork* brain);
    void randomResetting(NeuralNetwork* brain);

};