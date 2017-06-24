#pragma once
#include "RBFNeuronTemplate.h"
#include <math.h>
#include <assert.h>

class RadialNeuron : public RBFNeuronTemplate
{
private:
	double beta = 1;
	double center = 1;


public:
	RadialNeuron(double cent) : RBFNeuronTemplate(), center(cent)
	{
		lastInputValues_.resize(1);
	};
	~RadialNeuron();

	void feedData(std::vector<double> data)override
	{
		assert(data.size() == 1);
		lastExcitementValue_ = data[0] - center;
		lastInputValues_[0] = data[0];
		output_ = function(data[0]);
	}

	void backPropagation(std::vector<double> errors)override
	{
		assert(errors.size() == 1);
		error_ = derivative(output_) * errors[0];
	}

	void updateWeights(double learningFactor, double momentum)override
	{
		center += learningFactor * error_ *lastInputValues_[0] + previousValues[0]*momentum;
		previousValues[0] = learningFactor * error_ *lastInputValues_[0];
	}

	double function(double value)override
	{
		using std::pow;
		using std::exp;
		return exp(-pow(beta*(value - center), 2));
	}

	double derivative(double value)override
	{
		using std::pow;
		using std::exp;
		//return -2.0*beta*pow(value - center, 2) * exp(-(pow(beta*(center - value), 2)));
		return 2.0*pow(beta, 2)*(value - center)*exp(-(pow(beta,2)*pow(value - center,2)));
	}
};

