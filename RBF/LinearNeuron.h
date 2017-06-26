#pragma once
#include "RBFNeuronTemplate.h"
#include <numeric>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <random>

class LinearNeuron : public RBFNeuronTemplate
{
private:
	std::vector<double> inputWeights_;

public:
	LinearNeuron(int inputs) : RBFNeuronTemplate()
	{
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution(0, 1);

		inputWeights_ = std::vector<double>(inputs);
		transform(inputWeights_.begin(), inputWeights_.end(), inputWeights_.begin(), [&](const double& a)->double { return distribution(generator); });
		previousValues = std::vector<double>(inputs, 0);
	}

	~LinearNeuron();

	std::vector<double> getWeightedError() {
		using std::transform;

		std::vector<double> result(inputWeights_.size());
		transform(inputWeights_.cbegin(), inputWeights_.cend(), result.begin(), [&](double weight) { return weight*error_;  });
		return result;
	}

	void feedData(std::vector<double> data)override
	{
		assert(data.size() == inputWeights_.size());

		using std::accumulate;

		lastInputValues_ = data;
		lastExcitementValue_ = accumulate(
			data.cbegin(),
			data.cend(), 
			0.0, 
			[&, i = 0](const double& one, const double& two)mutable -> double { return (one + inputWeights_[i++] * two); }
		);
		output_ = function(lastExcitementValue_);
	}
	
	void backPropagation(std::vector<double> errors)override
	{
		error_ = errors[0];
	}

	void updateWeights(double learningFactor, double momentum)override
	{
		using std::for_each;
		for_each(inputWeights_.begin(), inputWeights_.end(), [this, &learningFactor, &momentum, i = 0](double& value)mutable { 
			value += momentum*previousValues[i];
			value += learningFactor*error_*lastInputValues_[i++]/* + momentum*previousValues[i++]*/; });
		for (int i = 0; i < inputWeights_.size(); i++) {
			previousValues[i] = learningFactor*error_*lastInputValues_[i];
		}
	}

	double function(double value)override
	{
		return value;
	}

	double derivative(double value)override
	{
		return 1;
	}
};

