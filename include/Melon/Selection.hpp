#pragma once
#include <Melon/NeuralNetwork.hpp>

enum SelectionMethod {
    ROULETTE
};

class Selection {
public:

    void init(int numBrains, int method);
    int* performSelection(NeuralNetwork* brains);
    void destroy();

private:

    int* defaultSelection();
    int* roulette(NeuralNetwork* brains);
    double getTotalFitness(NeuralNetwork* brains);

    int numParents;
    int numBrains;
    int method;
    int* parents;

};
