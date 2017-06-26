#include "RBFNetwork.h"



RBFNetwork::~RBFNetwork()
{
}

void RBFNetwork::initialize(int radialNeurons) {
	radialLayer.reserve(radialNeurons);
	linearLayer = std::vector<LinearNeuron>(outputDim, LinearNeuron(radialNeurons + (int)bias));
	std::default_random_engine generator;

	Kmeans kmeans(Kmeans::Init::Forgy, radialNeurons, data_, inputDim);
	while (kmeans.update());
	auto positions = kmeans.getCentroidsPositions();
	for (int i = 0; i < radialNeurons; i++) {
		radialLayer.push_back(RadialNeuron(positions[i]));
	}

	std::ofstream file("C:\\Users\\Latawiec\\Desktop\\RBFCentroids.txt", std::ios::trunc);
	file << kmeans.printCentroids();
	file.close();
}
