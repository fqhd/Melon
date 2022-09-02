#include <Melon/Selection.hpp>
#include <Melon/Random.hpp>
#include <iostream>

void Selection::init(int n, int m){
    numBrains = n;
    method = m;
    numParents = n * 2;

    parents.resize(numParents);
}

std::vector<NeuralNetwork> Selection::performSelection(const std::vector<NeuralNetwork>& brains){
    switch(method){
        case ROULETTE:
            roulette(brains);
        break;
        case RANK:
            rank(brains);
        break;
        default:
            roulette(brains);
        break;
    }
    return parents;
}

double getTotalFitness(const std::vector<NeuralNetwork>& brains){
    double total = 0;
    for(int i = 0; i < brains.size(); i++){
        total += brains[i].fitness;
    }
    return total;
}

 void Selection::roulette(const std::vector<NeuralNetwork>& brains){
    double totalFitness = getTotalFitness(brains);

    for(int i = 0; i < numParents; i++){
        double acc = 0.0;
        double r = Random::randomDouble(0.0, totalFitness);
        for(int j = 0; j < numBrains; j++){
            acc += brains[j].fitness;
            if(r < acc){
                parents[i] = brains[i];
                break;
            }
        }
    }
}

bool compare(const NeuralNetwork& a, const NeuralNetwork& b){
    return a.fitness > b.fitness;
}

NeuralNetwork selectRandom(const std::vector<NeuralNetwork>& brains){
    for(unsigned int i = 0; i < brains.size(); i++){
        int r = Random::randomInt(0, 1);
        if(r){
            brains[i];
        }
    }
    return brains[brains.size() - 1];
}

void Selection::rank(std::vector<NeuralNetwork> brains){
    std::sort(brains.begin(), brains.end(), compare);
    for(int i = 0; i < numParents; i++){
        parents[i] = selectRandom(brains);
    }
}

void Selection::destroy(){
    parents.clear();
}
