#include <iostream>
#include <string>
#include "Neuron.h"
#include "Group.h"

void main() {
	Neuron<int> a({ 5, 3, 5 });
	Group<int> group(a);
	std::cout << "Hello world!" << std::endl;
	std::cout << a.printWeights() << std::endl;
	std::getchar();
}