# Melon
Melon is a neuro-evolution library. Neuroevolution is the concept of using genetic algorithms to optimize neural networks. This library is both lightweight and implements many types of crossover, mutation, and selection to improve training.

## Adding to your project
If you are using cmake, adding the library to your project is incredibly easy. Simply clone the repository and call add_subdirectory() on wherever it has been downloaded. There currently is no support for other build systems.

## Example

```cpp
#include <iostream>
#include <Melon/GeneticAlgorithm.hpp>

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

    
    return 0;
}
```