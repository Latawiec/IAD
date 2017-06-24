#include "RBFNetwork.h"



RBFNetwork::~RBFNetwork()
{
}

void RBFNetwork::initialize(int radialNeurons) {
	radialLayer.reserve(radialNeurons);
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, data_.size() - 1);
	/*
	for (int i = 0; i < radialNeurons; i++) {
	radialLayer.push_back(RadialNeuron(data_[distribution(generator)][0]));
	}*/
	/*
	for (int i = 0; i < radialNeurons; i++) {
	int j = ((double)i / radialNeurons)*data_.size();
	radialLayer.push_back(RadialNeuron(data_[j][0]));
	}*/

	Kmeans kmeans(Kmeans::Init::Forgy, radialNeurons, data_, 1);
	while (kmeans.update());
	auto positions = kmeans.getCentroidsPositions();
	for (int i = 0; i < radialNeurons; i++) {
		radialLayer.push_back(RadialNeuron(positions[i][0]));
	}

	std::ofstream file("C:\\Users\\Latawiec\\Desktop\\RBFCentroids.txt", std::ios::trunc);
	file << kmeans.printCentroids();
	file.close();
}
