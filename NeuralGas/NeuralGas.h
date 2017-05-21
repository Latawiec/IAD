#pragma once
#include <random>
#include <fstream>
#include <memory>
#include <tuple>
#include "GasNeuron.h"
#include "MyMath.h"
#include <algorithm>
#include <mutex>

class NeuralGas
{
public:
	typedef std::vector<double> Point;

	NeuralGas(int neuronsNumber, std::string dataPath, double gridDistance = 1);
	~NeuralGas();

	bool update();
	double calculateDistanceFactor(int k);
	std::string printNeurons();
	int getIterations() { return iterations_; }

private:
	std::random_device generator_;
	std::uniform_int_distribution<int> distribution_;

	std::vector<GasNeuron> neurons_;
	std::vector<Point> points_;
	
	std::vector<std::tuple<GasNeuron*, double>> distances_;

	const double teachingFactor = 1;
	const double neighbourhoodRange = 0.5;
	const double minPotential_ = 0.95;
	const int numberOfNeurons_;
	int numberOfPoints_;

	int iterations_ = 0;
};

