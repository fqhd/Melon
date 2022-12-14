#include <Melon/Selection.hpp>
#include <Melon/Random.hpp>
#include <iostream>

Selection::Selection(){
    method = SelectionMethod::ROULETTE;
    K = 0;
}

std::vector<NeuralNetwork*> Selection::performSelection(const std::vector<NeuralNetwork*>& brains){
    parents.clear();
    switch(method){
        case SelectionMethod::ROULETTE:
            roulette(brains);
        break;
        case SelectionMethod::RANK:
            rank(brains);
        break;
        case SelectionMethod::STOCHASTIC_UNIVERSAL_SAMPLING:
            stochasticUniversalSampling(brains);
        break;
        case SelectionMethod::TOURNAMENT:
            tournamentSelection(brains);
        break;
        default:
            roulette(brains);
        break;
    }
    return parents;
}

double getTotalFitness(const std::vector<NeuralNetwork*>& brains){
    double total = 0;
    for(int i = 0; i < brains.size(); i++){
        total += brains[i]->fitness;
    }
    return total;
}

NeuralNetwork* getNeuralNetworkFromFitPos(const std::vector<NeuralNetwork*>& brains, double r){
    double acc = 0.0;
    for(int j = 0; j < brains.size(); j++){
        acc += brains[j]->fitness;
        if(r < acc){
            return brains[j];
        }
    }
    return brains[0];
}

void Selection::roulette(const std::vector<NeuralNetwork*>& brains){
    double totalFitness = getTotalFitness(brains);

    for(int i = 0; i < brains.size() * 2; i++){
        double r = Random::randomDouble(0.0, totalFitness);
        parents.push_back(getNeuralNetworkFromFitPos(brains, r));
    }
}

bool compare(const NeuralNetwork* a, const NeuralNetwork* b){
    return a->fitness > b->fitness;
}

// This function doesn't select a random neural network from the array. It selects the first one with 50%
// Chance, the second with 25% chance and so on until the end of the array. If none get selected, the last element
// In the array is returned
NeuralNetwork* selectRandom(const std::vector<NeuralNetwork*>& brains){
    for(unsigned int i = 0; i < brains.size(); i++){
        int r = Random::randomInt(0, 1);
        if(r){
            return brains[i];
        }
    }
    return brains[brains.size() - 1];
}

void Selection::rank(std::vector<NeuralNetwork*> brains){
    std::sort(brains.begin(), brains.end(), compare);
    for(int i = 0; i < brains.size() * 2; i++){
        parents.push_back(selectRandom(brains));
    }
}

void Selection::stochasticUniversalSampling(const std::vector<NeuralNetwork*>& brains){
    double totalFitness = getTotalFitness(brains); 
    double step = totalFitness / (brains.size() * 2);
    for(int i = 0; i < brains.size() * 2; i++){
        double fixedPoint = i * step;
        parents.push_back(getNeuralNetworkFromFitPos(brains, fixedPoint));
    }
}

void Selection::tournamentSelection(const std::vector<NeuralNetwork*>& brains){
    for(int i = 0; i < brains.size() * 2; i++){
        int highestFitnessIndex = Random::randomInt(0, (int)brains.size() - 1);
        for(int j = 0; j < K - 1; j++){
            int randomIndex = Random::randomInt(0, (int)brains.size() - 1);
            if(brains[randomIndex]->fitness > brains[highestFitnessIndex]->fitness){
                highestFitnessIndex = randomIndex;
            }
        }
        parents.push_back(brains[highestFitnessIndex]);
    }
}
