#include <Melon/Selection.hpp>
#include <Melon/Random.hpp>
#include <iostream>

void Selection::init(int n, int m){
    numBrains = n;
    method = m;
    numParents = n * 2;

    parents = (int*)malloc(sizeof(int) * numBrains * 2);
}

int* Selection::performSelection(const std::vector<NeuralNetwork>& brains){
    switch(method){
        case ROULETTE:
            return roulette(brains);
        break;
        case RANK:
            return rank(brains);
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

double Selection::getTotalFitness(const std::vector<NeuralNetwork>& brains){
    double total = 0;
    for(int i = 0; i < numBrains; i++){
        total += brains[i].fitness;
    }
    return total;
}

int* Selection::roulette(const std::vector<NeuralNetwork>& brains){
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

bool compare(const NeuralNetwork& a, const NeuralNetwork& b){
    return a.fitness > b.fitness;
}

double stretch(double x){
    return -pow((2 * x - 2), 2) + 1;
}

int selectRandom(const std::vector<NeuralNetwork>& brains){
    for(unsigned int i = 0; i < brains.size(); i++){
        int r = Random::randomInt(0, 1);
        if(r){
            return i;
        }
    }
    return brains.size() - 1;
}

int* Selection::rank(std::vector<NeuralNetwork> brains){
    std::sort(brains.begin(), brains.end(), compare);
    for(int i = 0; i < numParents; i++){
        parents[i] = selectRandom(brains);
    }
    return parents;
}

void Selection::destroy(){
    free(parents);
}
