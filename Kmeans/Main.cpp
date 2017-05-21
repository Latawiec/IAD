#include <iostream>
#include <string>
#include "Neuron.h"
#include "Group.h"
#include "Kmeans.h"

void main() {

	Kmeans k(Kmeans::Init::Forgy, 30, "C:\\Users\\Latawiec\\Desktop\\B.txt");

	while (k.update());

	std::ofstream file("C:\\Users\\Latawiec\\Desktop\\Centroids.txt", std::ios::trunc);
	file << k.printCentroids();
	file.close();

	file.open("C:\\Users\\Latawiec\\Desktop\\Points.txt", std::ios::trunc);
	file << k.printGroupedPoints();
	file.close();

	std::cout << "Hello world!" << std::endl;
	std::getchar();
}