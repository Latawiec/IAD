#include <iostream>
#include <string>
#include "Neuron.h"
#include "Group.h"
#include "Kmeans.h"

void main() {
	//Neuron<int> a({ 5, 3, 5 });
	//Group<int> group(a);

	Kmeans k(Kmeans::Init::Forgy, 3, "C:\\Users\\Latawiec\\Desktop\\a.txt");

	std::cout << "Hello world!" << std::endl;
	std::getchar();
}