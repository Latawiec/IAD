#pragma once
#include "RBFNeuronTemplate.h"
#include <math.h>
#include <assert.h>

class RadialNeuron : public RBFNeuronTemplate
{
private:
	double beta = 0.5;
	double center;

public:
	RadialNeuron(double center)
		: RBFNeuronTemplate(
	[&](double value)
	{ 
		using std::pow;
		using std::exp;
		return exp( -pow(beta*(value-center), 2) );
	},

	[&](double value)
	{ 
		using std::pow;
		using std::exp;
		return -2.0*beta* pow(value-center, 2) * exp( -( pow(beta, 2) * pow(center-value, 2)));
	}), center(center)
	{
		lastInputValues_.resize(1);
	};
	~RadialNeuron();

	void feedData(std::vector<double> data)override
	{
		assert(data.size() == 1);
		lastExcitementValue_ = beta*data[0];
		lastInputValues_[0] = data[0];
		output_ = function(data[0]);
	}

	void backPropagation(std::vector<double> errors)override
	{
		assert(errors.size() == 1);
		error_ = derivative(lastExcitementValue_) * errors[0];
	}

	void updateWeights(double learningFactor)override
	{
		beta += learningFactor * error_ * lastInputValues_[0];
	}
};

