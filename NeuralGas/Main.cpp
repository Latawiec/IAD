#include <iostream>
#include "NeuralGas.h"

void main()
{
	NeuralGas gas(100, "C:\\Users\\Latawiec\\Desktop\\B.txt", 0.1);

	while(gas.update() && gas.getIterations() < 1000);

	std::cout << gas.getIterations();

	std::ofstream file("C:\\Users\\Latawiec\\Desktop\\Neurons.txt", std::ios::trunc);
	file << gas.printNeurons();

	file.close();
	
	std::getchar();
}