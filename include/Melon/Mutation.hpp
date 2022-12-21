#pragma once

#include <Melon/NeuralNetwork.hpp>
#include <vector>

enum class MutationMethod : int {
    RANDOM_RESETTING,
    SCRAMBLE,
    NUDGE
};

class Mutation {
public:

    Mutation();
    void performMutation(const std::vector<NeuralNetwork*>& brains);

    float weightMutationChance;
    float biasMutationChance;
    float nudgeAmount;
    MutationMethod method;

private:

    void scrambleMutation(NeuralNetwork* brain);
    void nudgeMutation(NeuralNetwork* brain);
    void randomResetting(NeuralNetwork* brain);

};