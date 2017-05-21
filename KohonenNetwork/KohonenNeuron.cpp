#include "KohonenNeuron.h"

double KohonenNeuron::getTempDistance()
{
	return tempDistance_;
}

void KohonenNeuron::setTempDistance(double val)
{
	tempDistance_ = val;
}

double KohonenNeuron::getPotential()
{
	return potential_;
}

void KohonenNeuron::changePotential(double val)
{
	potential_ += val;
}
