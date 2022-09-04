#pragma once

#include <vector>
#include <Melon/NeuralNetwork.hpp>

enum CrossoverMethod {
    ONE_POINT_CROSSOVER
};

class Crossover {
public:

    void init(int numBrains, int method);
    std::vector<NeuralNetwork> performCrossover(const std::vector<NeuralNetwork>& parents);

private:

    std::vector<NeuralNetwork> children;
    NeuralNetwork(*crossoverFunc)(const NeuralNetwork&, const NeuralNetwork&);


};