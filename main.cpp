#include <iostream>
#include <Melon/GeneticAlgorithm.hpp>

int main(){

    GeneticAlgorithm algo;
    
    // This is the neural network model of all neural networks in the genetic algorithm
    Layer model[] = {
        {
            .activationFunc = NO_ACTIVATION_FUNCTION,
            .numNodes = 1
        },
        {
            .activationFunc = SIGMOID,
            .numNodes = 3
        },
        {
            .activationFunc = SOFTMAX,
            .numNodes = 2
        }
    };

    // Add a neural networks to the genetic algorithm
    // Every neural network in the genetic algorithm must have the same model
    // Note: The reason the NeuralNetwork class is coded in a way that allows neural networks to have different models is to allow the user to use the NeuralNetwork class in other areas of their code.
    for(int i = 0; i < 200; i++){
        algo.brains.push_back(new NeuralNetwork(model, 3, RANDOM_WEIGHT_INITIALIZATION));
    }

    // Initialize the genetic algorithm
    algo.init();

    // Add all neural networks you want to the genetic algorithm
    for(int i = 0; i < 200; i++){
        algo.brains.push_back(new NeuralNetwork(model, 3, RANDOM_WEIGHT_INITIALIZATION));
    }

    int numGenerations = 100;
    for(int i = 0; i < numGenerations; i++){
        // Here you would run a simulation for all neural networks in order to assign each of them a fitness value

        // This line runs the genetic algorithm(does selection, crossover, and mutation on the neural networks)
        algo.performGeneticAlgorithm();
    }

    // At this point neural networks should be trained. You would probably evalute the fitness values for all neural networks here and get the one with the highest fitness.

    // Destroy the genetic algorithm
    algo.destroy();

    return 0;
}