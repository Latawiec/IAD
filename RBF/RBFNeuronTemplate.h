#pragma once
#include <vector>
#include <functional>

class RBFNeuronTemplate
{

public:
	RBFNeuronTemplate(std::function<double(double)>&& function, std::function<double(double)>&& derivative)
		: function(std::move(function)), derivative(std::move(derivative)) {}

	~RBFNeuronTemplate();

	typedef std::vector<double> Point;
	virtual void feedData(std::vector<double> inputVector) = 0;
	virtual void backPropagation(std::vector<double> errors) = 0;
	virtual void updateWeights(double learningFactor) = 0;
	double getOutput()const { return output_;  }
	double getError()const { return error_; }

protected:
	std::function<double(double)> function;
	std::function<double(double)> derivative;
	double output_;
	double lastExcitementValue_;
	std::vector<double> lastInputValues_;
	double error_;
};

