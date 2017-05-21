#include "NeuralGas.h"



NeuralGas::NeuralGas(int neuronsNumber, std::string dataPath, double gridDistance)
	: numberOfNeurons_(neuronsNumber)
{
	std::ifstream file(dataPath);
	assert(file.is_open(), "File did not open properly. Aborting!");

	while (!file.eof()) {
		points_.push_back(Point(2));
		file >> points_.back()[0];
		file >> points_.back()[1];
	}
	file.close();

	numberOfPoints_ = points_.size();
	distances_ = std::vector<std::tuple<GasNeuron*, double>>(neuronsNumber, std::tuple<GasNeuron*, double>());
	distribution_ = std::uniform_int_distribution<int>(0, numberOfPoints_ - 1);

	int width = std::sqrt(numberOfNeurons_);

	for (int i = 0; i < neuronsNumber; i++) {
		neurons_.push_back(GasNeuron({gridDistance*(i%width), gridDistance*(i/width)}));
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
	for (std::tuple<GasNeuron*, double>& tuple : distances_) {
		std::get<1>(tuple) = euclideanDistance( std::get<0>(tuple)->getWeights(), *selected);
	}

	//Sort points according to their distances in vector 'distances_'
	std::sort(distances_.begin(), distances_.end(), [](const std::tuple<const GasNeuron*, double>& a, const std::tuple<const GasNeuron*, double>& b)->bool {
		return (std::get<1>(a) < std::get<1>(b));
	});

	//We need to start cooking... Update neurons weights!
	{
		std::vector<double> temp;
		int dim = selected->size();
		for (int i = 0; i < numberOfNeurons_; i++) {
			temp = std::vector<double>(std::get<0>(distances_[i])->getWeights());
			for (int j = 0; j < dim; j++) {
				temp[j] += teachingFactor*calculateDistanceFactor(i)*( (*selected)[j] - temp[j] );
			}
			std::get<0>(distances_[i])->setWeights(std::move(temp));
		}
	}

	iterations_++;
	return true;
}

double NeuralGas::calculateDistanceFactor(int k)
{
	return std::exp(-(double)k / neighbourhoodRange);
}

std::string NeuralGas::printNeurons()
{
	std::ostringstream str;
	for (int i = 0; i < numberOfNeurons_; i++) {
		str << '#' << i << '\n';
		str << neurons_[i].printWeights();
		str << '\n' << '\n' << '\n';
	}
	return str.str();
}
