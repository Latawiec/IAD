#pragma once
#include <vector> 
#include "RadialNeuron.h"
#include "LinearNeuron.h"
#include <string>
#include <fstream>
#include "Kmeans.h"
#include <random>
#include <sstream>

class RBFNetwork
{
	typedef std::vector<double> Point;
	bool bias;
public:
	RBFNetwork(std::string dataFile, int radialNeurons, int inputs, int outputs, bool bias = true) : bias(bias), inputDim(inputs), outputDim(outputs)
	{
		std::ifstream file(dataFile);
		assert(file.is_open());

		while (!file.eof()) {
			data_.push_back(Point(inputs+outputs));
			for_each(data_.back().begin(), data_.back().end(), [&file](double& value) { file >> value; });
		}
		file.close();

		initialize(radialNeurons);
	}
	~RBFNetwork();

	std::string feedData(std::string dataPath) {
		std::vector<Point> data;
		std::ifstream file(dataPath);
		assert(file.is_open());

		while (!file.eof()) {
			data.push_back(Point(inputDim + outputDim));
			for_each(data.back().begin(), data.back().end(), [&file](double& value) { file >> value; });
		}
		file.close();

		std::ostringstream str;

		using std::for_each;
		using std::transform;

		for_each(data.cbegin(), data.cend(),
			[&](const Point& dataPoint)
		{
			//Feeding Data
			for (RadialNeuron& neuron : radialLayer) {
				neuron.feedData(std::vector<double>(&dataPoint[0], &dataPoint[inputDim]));
			}

			{
				std::vector<double> radialOutput(radialLayer.size());
				transform(radialLayer.cbegin(), radialLayer.cend(), radialOutput.begin(), [](const RadialNeuron& neuron)->double { return neuron.getOutput(); });
				if (bias) radialOutput.push_back(1);
				for_each(linearLayer.begin(), linearLayer.end(), [&radialOutput](LinearNeuron& neuron) { neuron.feedData(radialOutput); });
			}

			for (int i = 0; i < inputDim; i++) { str << dataPoint[i] << '\t'; }
			for (int i = 0; i < outputDim; i++) { str << linearLayer[i].getOutput() << '\t'; }
			str << '\n';
		});

		return str.str();
	}

	std::string feedData() {
		std::ostringstream str;

		using std::for_each;
		using std::transform;

		for_each(data_.cbegin(), data_.cend(),
			[&](const Point& dataPoint)
		{
			//Feeding Data
			for (RadialNeuron& neuron : radialLayer) {
				neuron.feedData(std::vector<double>(&dataPoint[0], &dataPoint[inputDim]));
			}

			{
				std::vector<double> radialOutput(radialLayer.size());
				transform(radialLayer.cbegin(), radialLayer.cend(), radialOutput.begin(), [](const RadialNeuron& neuron)->double { return neuron.getOutput(); });
				if (bias) radialOutput.push_back(1);
				for_each(linearLayer.begin(), linearLayer.end(), [&radialOutput](LinearNeuron& neuron) { neuron.feedData(radialOutput); });
			}

			for (int i = 0; i < inputDim; i++) { str << dataPoint[i] << '\t'; }
			for (int i = 0; i < outputDim; i++) { str << linearLayer[i].getOutput() << '\t'; }
			str << '\n';
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
				neuron.feedData(std::vector<double>(&dataPoint[0], &dataPoint[inputDim]));
			}

			{
				std::vector<double> radialOutput(radialLayer.size());
				transform(radialLayer.cbegin(), radialLayer.cend(), radialOutput.begin(), [](const RadialNeuron& neuron)->double { return neuron.getOutput(); });
				if (bias) radialOutput.push_back(1);
				for_each(linearLayer.begin(), linearLayer.end(), [&radialOutput](LinearNeuron& neuron) { neuron.feedData(radialOutput); });
			}

			//Propagating error
			for_each(linearLayer.begin(), linearLayer.end(), [&, i = 0](LinearNeuron& neuron)mutable { neuron.backPropagation({ dataPoint[inputDim + i++] - neuron.getOutput() }); });

			//Update weights
			for_each(linearLayer.begin(), linearLayer.end(), [&](LinearNeuron& neuron) { neuron.updateWeights(learningFactor, momentum); });
		});
	}
	

private:
	void initialize(int radialNeurons);

	std::vector<RadialNeuron> radialLayer;
	std::vector<LinearNeuron> linearLayer;

	const int inputDim;
	const int outputDim;

	std::vector<Point> data_;
	double learningFactor = 0.4;
	double momentum = 0.05;
};