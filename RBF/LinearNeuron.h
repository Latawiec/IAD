#pragma once
#include "RBFNeuronTemplate.h"
#include <numeric>
#include <algorithm>
#include <assert.h>

class LinearNeuron : public RBFNeuronTemplate
{
private:
	std::vector<double> inputWeights_;

public:
	LinearNeuron(int inputs)
		: RBFNeuronTemplate(
			[&](double value) { return value; },
			[&](double value) { return 1; })
	{
		inputWeights_ = std::vector<double>(inputs, 0.5);
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
			[&, i = 0](double one, double two)mutable -> double { return inputWeights_[i++] * (one + two); }
		);
		output_ = function(lastExcitementValue_);
	}
	
	void backPropagation(std::vector<double> errors)override
	{
		using std::accumulate;
		error_ = derivative(lastExcitementValue_)*accumulate(errors.cbegin(), errors.cend(), 0.0, [](double one, double two) { return one + two; });
	}

	void updateWeights(double learningFactor)override
	{
		using std::for_each;
		for_each(inputWeights_.begin(), inputWeights_.end(), [&, i = 0](double& value)mutable { value += learningFactor*error_*lastInputValues_[i++]; });
	}
};

