#include <iostream>
#include "NeuralGas.h"

void main()
{
	NeuralGas gas(36, "C:\\Users\\Latawiec\\Desktop\\B.txt");
	while(gas.update() && gas.getIterations() < 150000);

	std::cout << gas.getIterations();

	std::ofstream file("C:\\Users\\Latawiec\\Desktop\\Neurons.txt", std::ios::trunc);
	file << gas.printNeurons();
	file.close();
	
	std::getchar();
}