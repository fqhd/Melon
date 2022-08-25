#pragma once
#include <Melon/NeuralNetwork.hpp>
#include <vector>

enum SelectionMethod {
    ROULETTE,
    RANK
};

class Selection {
public:

    void init(int numBrains, int method);
    int* performSelection(const std::vector<NeuralNetwork>& brains);
    void destroy();

private:

    int* defaultSelection();
    int* roulette(const std::vector<NeuralNetwork>& brains);
    int* rank(std::vector<NeuralNetwork> brains);
    double getTotalFitness(const std::vector<NeuralNetwork>& brains);

    int numParents;
    int numBrains;
    int method;
    int* parents;

};
