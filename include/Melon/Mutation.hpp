#pragma once

#include <Melon/NeuralNetwork.hpp>
#include <vector>

enum MutationMethods {
    RANDOM_RESETTING,
    SCRAMBLE_MUTATION
};

class Mutation {
public:

    Mutation(int method);
    void performMutation(const std::vector<NeuralNetwork*>& brains);

private:

    void(*mutationFunc)(NeuralNetwork*);

};