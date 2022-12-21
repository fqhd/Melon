#pragma once
#include <Melon/NeuralNetwork.hpp>
#include <vector>

enum class SelectionMethod : int {
    ROULETTE,
    RANK,
    STOCHASTIC_UNIVERSAL_SAMPLING,
    TOURNAMENT,
};

class Selection {
public:

    Selection();
    std::vector<NeuralNetwork*> performSelection(const std::vector<NeuralNetwork*>& brains);

    int K;
    SelectionMethod method;

private:

    void roulette(const std::vector<NeuralNetwork*>& brains);
    void rank(std::vector<NeuralNetwork*> brains);
    void stochasticUniversalSampling(const std::vector<NeuralNetwork*>& brains);
    void tournamentSelection(const std::vector<NeuralNetwork*>& brains);

    std::vector<NeuralNetwork*> parents;

};
