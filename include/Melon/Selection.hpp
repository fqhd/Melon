#pragma once
#include <Melon/NeuralNetwork.hpp>
#include <vector>

enum SelectionMethod {
    ROULETTE_SELECTION,
    RANK_SELECTION,
    STOCHASTIC_UNIVERSAL_SAMPLING,
    TOURNAMENT_SELECTION,
};

class Selection {
public:

    void init(int numBrains);
    std::vector<NeuralNetwork*> performSelection(const std::vector<NeuralNetwork*>& brains);

    int K = 0;
    int method = ROULETTE_SELECTION;

private:

    void roulette(const std::vector<NeuralNetwork*>& brains);
    void rank(std::vector<NeuralNetwork*> brains);
    void stochasticUniversalSampling(const std::vector<NeuralNetwork*>& brains);
    void tournamentSelection(const std::vector<NeuralNetwork*>& brains);

    int numParents;
    int numBrains;
    std::vector<NeuralNetwork*> parents;

};
