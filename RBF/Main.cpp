#include<iostream>
#include "RBFNetwork.h"

void main()
{
	RBFNetwork network("C://Users//Latawiec//Desktop//dupa.txt", 12, true);
	for (int i = 0; i < 1200; i++)
		network.teach();
	std::cout << "Hello RBF!" << std::endl;
	
	std::ofstream file("C:\\Users\\Latawiec\\Desktop\\dupaWynik.txt", std::ios::trunc);
	file << network.feedData("C://Users//Latawiec//Desktop//dupaMax.txt");
	file.close();

	std::getchar();
}