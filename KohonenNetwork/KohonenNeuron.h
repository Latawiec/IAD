#pragma once
#include "Neuron.h"

class KohonenNeuron : public Neuron<double>
{
public:
	KohonenNeuron(std::initializer_list<double> &&values) : Neuron(std::move(values)) {}
	KohonenNeuron(std::vector<double> &&values) : Neuron(std::move(values)) {}
	KohonenNeuron(const std::vector<double> &values) : Neuron(values) {}
	~KohonenNeuron() {};
	double getTempDistance();
	void setTempDistance(double val);
	double getPotential();
	void changePotential(double val);

private:
	double tempDistance_;
	double potential_ = 1;
};

