#pragma once
#include <Melon/NeuralNetwork.hpp>

#define ROULETTE 0

class Selection {
public:

    void init(int numBrains, int method = 0);
    int* performSelection(NeuralNetwork* brains);
    void destroy();

private:

    int* defaultSelection();

    int numParents;
    int numBrains;
    int method;
    int* parents;

};
