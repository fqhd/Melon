#include <iostream>
#include <Agent/NeuralNetwork.hpp>
#include <Agent/Random.hpp>

int main(){
    Layer model[] = {
        {
            .activationFunc = RELU,
            .numNodes = 3
        },
        {
            .activationFunc = RELU,
            .numNodes = 4
        },
        {
            .activationFunc = LEAKY_RELU,
            .numNodes = 2
        }
    };
    Random::seed(time(0));
    NeuralNetwork nn(model, sizeof(model)/sizeof(model[0]));
    for(int i = 0; i < nn.getNumWeights(); i++){
        nn.weights[i] = Random::randomFloat(-1.0f, 1.0f);
    }
    for(int i = 0; i < nn.getNumBiases(); i++){
        nn.biases[i] = Random::randomFloat(-1.0f, 1.0f);
    }

    float data[] = {
        1.0f, 1.0f, 1.0f
    };

    float* output = nn.predict(data, sizeof(data)/sizeof(data[0]));

    std::cout << output[0] + output[1] << std::endl;
    nn.save("nn.bin");
    return 0;
}