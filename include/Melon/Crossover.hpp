#pragma once

#include <vector>
#include <Melon/NeuralNetwork.hpp>

enum CrossoverMethod {
    ONE_POINT_CROSSOVER
};

class Crossover {
public:

    Crossover(Layer* model, int numLayers, int numBrains, int method);
    std::vector<NeuralNetwork*> performCrossover(const std::vector<NeuralNetwork*>& parents);

private:

    std::vector<NeuralNetwork*> children;
    void(*crossoverFunc)(const NeuralNetwork*, const NeuralNetwork*, NeuralNetwork* child);


};