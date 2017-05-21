#include <iostream>
#include "KohonenNet.h"

int main()
{
	KohonenNet SOM(30, "X:\\POLIBUDA\\PROJEKTY\\IAD\\1312\\Data\\B.txt");	
	while (SOM.update() && SOM.getIterations() < 150000);

	std::cout << SOM.getIterations();

	//std::ofstream file("X:\\POLIBUDA\\PROJEKTY\\IAD\\1312\\Data\\KohonenNeurons.txt", std::ios::trunc);
	std::ofstream file("X:\\gnuplot\\bin\\KohonenNeurons.txt", std::ios::trunc);
	file << SOM.printNeurons();
	file.close();	
	std::cout << "Hello world!"; 
	std::getchar();
}