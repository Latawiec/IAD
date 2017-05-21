#pragma once
#include "Group.h"


class GasNeuron : public Neuron<double> 
{
public:
	GasNeuron(std::initializer_list<double> &&values) : Neuron(std::move(values)) {}
	GasNeuron(std::vector<double> &&values) : Neuron(std::move(values)) {}
	GasNeuron(const std::vector<double> &values) : Neuron(values) {}
	~GasNeuron() {};

	double getPotential() { return potential_; }
	void addPotential(double value) { potential_ += value; }

private:
	double potential_ = 1;
};

