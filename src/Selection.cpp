#include <Melon/Selection.hpp>
#include <cstdlib>

void Selection::init(int n, int m){
    numBrains = n;
    method = m;
    numParents = n * 2;

    parents = (int*)malloc(sizeof(int) * numBrains * 2);
}

int* Selection::performSelection(NeuralNetwork* brains){
    for(int i = 0; i < numParents; i++){
        parents[i] = 0;
    }
    return parents;
}

void Selection::destroy(){
    free(parents);
}