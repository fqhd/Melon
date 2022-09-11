#pragma once

#include <vector>
#include <Melon/NeuralNetwork.hpp>

enum CrossoverMethod {
    ONE_POINT_CROSSOVER,
    UNIFORM_CROSSOVER,
    AVERAGE_CROSSOVER
};

class Crossover {
public:

    Crossover();
    void init(Layer* model, int numLayers, int numBrains);
    void destroy();
    std::vector<NeuralNetwork*> performCrossover(const std::vector<NeuralNetwork*>& parents);

    int method;

private:

    std::vector<NeuralNetwork*> children;
    void(*crossoverFunc)(const NeuralNetwork*, const NeuralNetwork*, NeuralNetwork*);


};