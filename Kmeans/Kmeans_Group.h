#pragma once
#include "Group.h"

class Kmeans_Group : public Group<double>
{
public:
	Kmeans_Group(Neuron<double>& parent) : Group<double>(parent) {};
	Kmeans_Group(Neuron<double>&& parent) : Group<double>(parent) {};
	~Kmeans_Group() {};

	bool updateParentWeights(); //Returns false if parent hasn't moved at all.
};

