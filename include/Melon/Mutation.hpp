#pragma once

#include <Melon/NeuralNetwork.hpp>
#include <vector>

enum MutationMethods {
    RANDOM_RESETTING
};

class Mutation {
public:

    Mutation(int method);
    void performMutation(const std::vector<NeuralNetwork*>& brains);

private:

    void(*mutateBrain)(NeuralNetwork*);

};