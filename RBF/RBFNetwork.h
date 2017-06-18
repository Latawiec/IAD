#pragma once
#include <vector> 
#include "RadialNeuron.h"
#include "LinearNeuron.h"
#include <string>
#include <fstream>
#include <random>
#include <sstream>

class RBFNetwork
{
	typedef std::vector<double> Point;

public:
	RBFNetwork(std::string dataFile, int numberOfNeurons = 5) : linearNeuron(numberOfNeurons)
	{
		std::ifstream file(dataFile);
		assert(file.is_open());

		while (!file.eof()) {
			data_.push_back(Point(2));
			file >> data_.back()[0];
			file >> data_.back()[1];
		}
		file.close();

		initialize(numberOfNeurons);
	}
	~RBFNetwork();

	std::string feedData() {
		std::vector<Point> result;
		std::ostringstream str;

		using std::for_each;
		using std::transform;

		for_each(data_.cbegin(), data_.cend(),
			[&](const Point& dataPoint)
		{
			//Feeding Data
			for (RadialNeuron& neuron : radialLayer) {
				neuron.feedData({ dataPoint[0] });
			}

			{
				std::vector<double> radialOutput(radialLayer.size());
				transform(radialLayer.cbegin(), radialLayer.cend(), radialOutput.begin(), [](const RadialNeuron& neuron)->double { return neuron.getOutput(); });
				linearNeuron.feedData(radialOutput);
			}

			str << dataPoint[0] << '\t' << linearNeuron.getOutput() << '\n';
		});

		return str.str();
	}

	void teach()
	{
		using std::for_each;
		using std::transform;

		for_each(data_.cbegin(), data_.cend(), 
		[&](const Point& dataPoint)
		{
			//Feeding Data
			for (RadialNeuron& neuron : radialLayer) {
				neuron.feedData({dataPoint[0]});
			}

			{
				std::vector<double> radialOutput(radialLayer.size());
				transform(radialLayer.cbegin(), radialLayer.cend(), radialOutput.begin(), [](const RadialNeuron& neuron)->double { return neuron.getOutput(); });
				linearNeuron.feedData(radialOutput);
			}

			//Propagating error
			{
				linearNeuron.backPropagation({ dataPoint[1] - linearNeuron.getOutput() });
				std::vector<double> weightedErrors = linearNeuron.getWeightedError();
				for_each(radialLayer.begin(), radialLayer.end(), [&, i = 0](RadialNeuron& neuron)mutable{ neuron.backPropagation({ weightedErrors[i++] }); });
			}

			//Update weights
			for (RadialNeuron& neuron : radialLayer) {
				neuron.updateWeights(learningFactor);
			}
			linearNeuron.updateWeights(learningFactor);
		});
	}
	

private:
	void initialize(int radialNeurons) {
		radialLayer.reserve(radialNeurons);
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, data_.size()-1);

		for (int i = 0; i < radialNeurons; i++) {
			radialLayer.push_back(RadialNeuron(distribution(generator)));
		}
	}

	std::vector<RadialNeuron> radialLayer;
	LinearNeuron linearNeuron;

	std::vector<Point> data_;
	double learningFactor = 0.5;
};