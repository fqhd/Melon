# CPPNN
Simple Neural Network Class for learning purposes, (not GPU accelerated at all or optimized in anyway). Specifically made for educational purposes only.

## Adding to your project
To add the library to your project, simply clone the repo and place it somewhere in your project then call add_subdirectory() on it.

## Example

```cpp
#include <iostream>
#include <Agent/NeuralNetwork.hpp>

int main(){
    // Specify your model architecture.
    // Currently, all layers are dense layers by default with a
    // modifyable number of nodes and activation functions.
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

    // Constructor doesn't initialize weights(not even with 0s), it only allocates memory for them.
    // Weight initialization is up to the user
    NeuralNetwork nn(model, sizeof(model)/sizeof(model[0]));
    for(int i = 0; i < nn.getNumWeights(); i++){
        nn.weights[i] = rand() % 1000 / 999.0f;
    }
    for(int i = 0; i < nn.getNumBiases(); i++){
        nn.biases[i] = rand() % 1000 / 999.0f;
    }

    // Input data to the network
    float data[] = {
        1.0f, 1.0f, 1.0f
    };

    // Do not free this pointer. It will return a pointer to an array of outputs, but do not free it.
    float* output = nn.predict(data, sizeof(data)/sizeof(data[0]));

    std::cout << output[0] + output[1] << std::endl;

    // You can also save the neural network to a binary file.
    nn.save("nn.bin");

    // If you'd like to load the neural network from a file, pass a path to the constructor:
    NeuralNetwork otherNN("nn.bin");
    return 0;
}
```