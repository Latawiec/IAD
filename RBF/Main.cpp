#include<iostream>
#include "RBFNetwork.h"

void main()
{
	RBFNetwork network("C://Users//Latawiec//Desktop//dupa.txt", 30);
	network.teach();
	std::cout << "Hello RBF!" << std::endl;
	
	std::ofstream file("C:\\Users\\Latawiec\\Desktop\\dupaWynik.txt", std::ios::trunc);
	file << network.feedData();
	file.close();

	std::getchar();
}