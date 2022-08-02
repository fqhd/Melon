#include <iostream>
#include <Agent/NeuralNetwork.hpp>

int main(){
    int model[] = {3, 4, 2};
    Random random;
    NeuralNetwork nn(model, sizeof(model)/sizeof(model[0]), &random);

    float data[] = {
        1.0f, 1.0f, 1.0f
    };

    float* output = nn.predict(data, 3);

    return 0;
}