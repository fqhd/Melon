#include <Melon/Selection.hpp>
#include <Melon/Random.hpp>
#include <iostream>

void Selection::init(int nb, int m){
    numBrains = nb;
    method = m;
    numParents = nb * 2;

    parents.resize(numParents);
}

std::vector<NeuralNetwork> Selection::performSelection(const std::vector<NeuralNetwork>& brains){
    switch(method){
        case ROULETTE_SELECTION:
            roulette(brains);
        break;
        case RANK_SELECTION:
            rank(brains);
        break;
        case STOCHASTIC_UNIVERSAL_SAMPLING:
            stochasticUniversalSampling(brains);
        break;
        case TOURNAMENT_SELECTION:
            tournamentSelection(brains);
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

NeuralNetwork getNeuralNetworkFromFitPos(const std::vector<NeuralNetwork>& brains, double r){
    double acc = 0.0;
    for(int j = 0; j < brains.size(); j++){
        acc += brains[j].fitness;
        if(r < acc){
            return brains[j];
        }
    }
    return brains[0];
}

void Selection::roulette(const std::vector<NeuralNetwork>& brains){
    double totalFitness = getTotalFitness(brains);

    for(int i = 0; i < numParents; i++){
        double r = Random::randomDouble(0.0, totalFitness);
        parents[i] = getNeuralNetworkFromFitPos(brains, r);
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

void Selection::stochasticUniversalSampling(const std::vector<NeuralNetwork>& brains){
    double totalFitness = getTotalFitness(brains); 
    double step = totalFitness / numParents;
    for(int i = 0; i < numParents; i++){
        double fixedPoint = i * step;
        parents[i] = getNeuralNetworkFromFitPos(brains, fixedPoint);
    }
}

void Selection::tournamentSelection(const std::vector<NeuralNetwork>& brains){
    int K = numParents * 0.01;
    
    for(int i = 0; i < numParents; i++){
        int highestFitnessIndex = Random::randomInt(0, numBrains - 1);
        for(int j = 0; j < K - 1; j++){
            int randomIndex = Random::randomInt(0, numBrains - 1);
            if(brains[randomIndex].fitness > brains[highestFitnessIndex].fitness){
                highestFitnessIndex = randomIndex;
            }
        }
        parents[i] = brains[highestFitnessIndex];
    }
}
