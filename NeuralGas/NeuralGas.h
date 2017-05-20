#pragma once
#include <random>
#include <fstream>
#include <memory>
#include <tuple>
#include "GasNeuron.h"
#include "MyMath.h"
#include <algorithm>

class NeuralGas
{
public:
	typedef std::vector<double> Point;

	NeuralGas(int neuronsNumber, std::string dataPath, double gridDistance = 0.1);
	~NeuralGas();

	bool update();
	double calculateDistanceFactor(int k);

private:
	std::random_device generator_;
	std::uniform_int_distribution<int> distribution_;

	std::vector<GasNeuron> neurons_;
	std::vector<Point> points_;
	
	std::vector<std::tuple<const GasNeuron*, double>> distances_;

	const double teachingFactor = 0.7;
	const double neighbourhoodRange = 0.8;
	const int numberOfNeurons_;
	int numberOfPoints_;
};

