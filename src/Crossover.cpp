#include <Melon/Crossover.hpp>

void onePointCrossover(const NeuralNetwork* parent1, const NeuralNetwork* parent2, NeuralNetwork* child){

}

Crossover::Crossover(Layer* model, int numLayers, int numBrains, int method){
    for(int i = 0; i < numBrains; i++){
        children.push_back(new NeuralNetwork(model, numLayers, RANDOM_WEIGHT_INITIALIZATION));
    }
    switch(method){
        case ONE_POINT_CROSSOVER:
            crossoverFunc = onePointCrossover;
        break;
    };
}

std::vector<NeuralNetwork*> Crossover::performCrossover(const std::vector<NeuralNetwork*>& parents){
    int index = 0;
    for(int i = 0; i < children.size(); i++){
        int p1 = index;
        int p2 = index+1;
        crossoverFunc(parents[p1], parents[p2], children[i]);
        index += 2;
    }
}

