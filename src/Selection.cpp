#include <Melon/Selection.hpp>
#include <Melon/Random.hpp>
#include <iostream>

void Selection::init(int n, int m){
    numBrains = n;
    method = m;
    numParents = n * 2;

    parents = (int*)malloc(sizeof(int) * numBrains * 2);
}

int* Selection::performSelection(NeuralNetwork* brains){
    switch(method){
        case ROULETTE:
            return roulette(brains);
        break;

        default:
            return defaultSelection();
        break;
    }
}

int* Selection::defaultSelection(){
    for(int i = 0; i < numParents; i++){
        parents[i] = 0;
    }
    return parents;
}

double Selection::getTotalFitness(NeuralNetwork* brains){
    double total = 0;
    for(int i = 0; i < numBrains; i++){
        total += brains[i].fitness;
    }
    return total;
}

int* Selection::roulette(NeuralNetwork* brains){
    double totalFitness = getTotalFitness(brains);

    for(int i = 0; i < numParents; i++){
        double acc = 0.0;
        double r = Random::randomDouble(0.0, totalFitness);
        for(int j = 0; j < numBrains; j++){
            acc += brains[j].fitness;
            if(r < acc){
                parents[i] = j;
                break;
            }
        }
    }
    return parents;
}

void Selection::destroy(){
    free(parents);
}
