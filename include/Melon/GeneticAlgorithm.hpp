#pragma once
#include <cstdint>
#include <vector>
#include <Melon/NeuralNetwork.hpp>
#include <Melon/Selection.hpp>
#include <Melon/Crossover.hpp>
#include <Melon/Mutation.hpp>

class GeneticAlgorithm {
public:

    void init();
    void performGeneticAlgorithm();
    void destroy();
    
    std::vector<NeuralNetwork*> brains;

private:

    Selection selection;
    Crossover crossover;
    Mutation mutation;

};