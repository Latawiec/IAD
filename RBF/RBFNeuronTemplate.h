#pragma once
#include <vector>
#include <functional>

class RBFNeuronTemplate
{

public:
	RBFNeuronTemplate() {}

	~RBFNeuronTemplate();

	typedef std::vector<double> Point;
	virtual void feedData(std::vector<double> inputVector) = 0;
	virtual void backPropagation(std::vector<double> errors) = 0;
	virtual void updateWeights(double learningFactor, double momentum) = 0;
	double getOutput()const { return output_;  }
	double getError()const { return error_; }

protected:
	virtual double function(double value) = 0;
	virtual double derivative(double value) = 0;
	double output_;
	double lastExcitementValue_;
	std::vector<double> lastInputValues_;
	double error_;
	std::vector<double> previousValues = std::vector<double>(1, 0);
};

