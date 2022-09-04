#include <Melon/Crossover.hpp>


NeuralNetwork onePointCrossover(const NeuralNetwork& parent1, const NeuralNetwork& parent2){
    return parent1;
}

void Crossover::init(int numBrains, int method){
    children.resize(numBrains);
    switch(method){
        case ONE_POINT_CROSSOVER:
            crossoverFunc = onePointCrossover;
        break;
    };
}

std::vector<NeuralNetwork> Crossover::performCrossover(const std::vector<NeuralNetwork>& parents){
    int index = 0;
    for(int i = 0; i < children.size(); i++){
        int p1 = index;
        int p2 = index+1;
        children[i] = crossoverFunc(parents[p1], parents[p2]);
        index += 2;
    }
}

