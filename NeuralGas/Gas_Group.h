#pragma once
#include "Group.h"


class Gas_Group : public Group<double> 
{
public:
	Gas_Group(Neuron<double>& parent) : Group<double>(parent) {}
	Gas_Group(Neuron<double>&& parent) : Group<double>(std::move(parent)) {}
	~Gas_Group() {};
};

