#include <iostream>
#include <string>
#include "Neuron.h"


void main() {
	Neuron<int> a({ 5, 3, 5 });

	std::cout << "Hello world!" << std::endl;
	std::cout << a.printWeights() << std::endl;
	std::getchar();
}