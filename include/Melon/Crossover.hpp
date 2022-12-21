#pragma once

#include <vector>
#include <Melon/NeuralNetwork.hpp>

enum class CrossoverMethod : int {
    ONE_POINT,
    UNIFORM,
    AVERAGE
};

class Crossover {
public:

    void init(Layer* model, int numLayers, int numBrains);
    void destroy();
    std::vector<NeuralNetwork*> performCrossover(const std::vector<NeuralNetwork*>& parents);

    CrossoverMethod method;

private:

    std::vector<NeuralNetwork*> children;
    void(*crossoverFunc)(const NeuralNetwork*, const NeuralNetwork*, NeuralNetwork*);


};