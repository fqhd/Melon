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
    std::vector<NeuralNetwork> performSelection(const std::vector<NeuralNetwork>& brains);
    void destroy();

private:

    void roulette(const std::vector<NeuralNetwork>& brains);
    void rank(std::vector<NeuralNetwork> brains);

    int numParents;
    int numBrains;
    int method;
    std::vector<NeuralNetwork> parents;

};
