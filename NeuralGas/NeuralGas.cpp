#include "NeuralGas.h"



NeuralGas::NeuralGas(int neuronsNumber, std::string dataPath, double gridDistance)
	: numberOfNeurons_(neuronsNumber)
{
	std::ifstream file(dataPath);
	assert(file.is_open());

	while (!file.eof()) {
		points_.push_back(Point(2));
		file >> points_.back()[0];
		file >> points_.back()[1];
	}
	file.close();

	numberOfPoints_ = points_.size();
	distances_ = std::vector<std::tuple<const GasNeuron*, double>>(neuronsNumber, std::tuple<const GasNeuron*, double>());
	distribution_ = std::uniform_int_distribution<int>(0, numberOfPoints_ - 1);

	for (int i = 0; i < neuronsNumber; i++) {
		neurons_.push_back(GasNeuron({0, i*gridDistance}));
	}

	for (int i = 0; i < neuronsNumber; i++) {
		std::get<0>(distances_[i]) = &(neurons_[i]);
	}
}


NeuralGas::~NeuralGas()
{
}

bool NeuralGas::update()
{
	//Randomly choose point to be selected.
	const Point* selected = &(points_[distribution_(generator_)]);

	//Calculate distances to each of neurons and store them in the sexy vector of tuples.
	for (auto& tuple : distances_) {
		std::get<1>(tuple) = euclideanDistance( std::get<0>(tuple)->getWeights(), *selected);
	}

	//Sort points according to their distances in vector 'distances_'
	std::sort(distances_.begin(), distances_.end(), [](const auto& a, const auto& b)->bool {
		return (std::get<1>(a) < std::get<1>(b));
	});

	return false;
}

double NeuralGas::calculateDistanceFactor(int k)
{
	return std::exp(-(double)k / neighbourhoodRange);
}
