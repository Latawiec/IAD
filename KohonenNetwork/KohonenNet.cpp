#include "KohonenNet.h"
#include <iostream>

KohonenNet::KohonenNet(int neuronsNumber, std::string dataPath)
	: numberOfNeurons_(neuronsNumber)
{
	std::ifstream file(dataPath);
	assert(file.is_open());
	
	while (!file.eof()) {
		points_.push_back(Point(2));
		file >> points_.back()[0];
		file >> points_.back()[1];
	}
	file.close();

	numberOfPoints_ = points_.size();
	
	distribution_ = std::uniform_int_distribution<int>(0, numberOfPoints_ - 1);
	width_ = std::sqrt(numberOfNeurons_);

	//making vectors in vector
	for (int i = 0; i < width_; i++)
	{
		neurons_.push_back(std::vector<KohonenNeuron>());
	}
	//making grid.
	for (int i = 0; i < numberOfNeurons_; i++) {
		neurons_[i%width_].push_back(KohonenNeuron({ 0.1*(i%width_), 0.1*(i / width_) }));
	}
}

KohonenNet::~KohonenNet()
{
}

bool KohonenNet::update()
{	
	const Point* selected = &(points_[distribution_(generator_)]);
	KohonenNeuron* current = nullptr;
	int wi, wj; //position in grid for winner
	double best = DBL_MAX; //winner, grubo albo wcale
	//calcluate distances and find winner
	for (int i=0; i<neurons_.size(); i++)
	{
		for (int j = 0; j<neurons_[i].size(); j++)
		{
			current = &(neurons_[i][j]);
			current->setTempDistance(euclideanDistance(current->getWeights(), *selected)); //set euc distance for selected point
			if (current->getTempDistance() < best  && current->getPotential()>minPotential_) //chceck if potential is enough to win
			{
				best = current->getTempDistance();
				wi = i;
				wj = j;
			}
		}
	}

	//do the show.
	int dim = selected->size();
	std::vector<double> temp;
	for (int i = 0; i < neurons_.size(); i++)
	{
		for (int j = 0; j < neurons_[i].size(); j++)
		{														 //for each neuron 
			current = &(neurons_[i][j]);
			const int neighbourhoodLayer = abs(wi - i) + abs(wj - j);	 //calculate distance in _ _ _ (to ma swoj¹ nazwê, ale nie wiem)
			temp = current->getWeights();
			for (int d = 0; d < dim; d++) {
				temp[d] += teachingFactor*calculateDistanceFactor(neighbourhoodLayer)*((*selected)[d] - temp[d]); //teaching
			}
			current->setWeights(std::move(temp));
			if (neighbourhoodLayer == 0)
			{
				current->changePotential(minPotential_ * -1.0); //if winner				
			}
			else
			{
				current->changePotential(1.0 / numberOfNeurons_); //others				
			}
		}
	}
	iterations_++;
	if (iterations_ % 5000 == 0) { std::cout << iterations_ << std::endl; }
	return true;
}

double KohonenNet::calculateDistanceFactor(int k)
{		
	if(k<=neighbourhoodRange)	return std::exp(-(double)k / 2*neighbourhoodRange*neighbourhoodRange);
	return 0;
}




std::string KohonenNet::printNeurons()
{
	std::ostringstream str;
	int k = 0;
	for (int i = 0; i<neurons_.size(); i++)
	{
		for (int j = 0; j < neurons_[i].size(); j++)
		{
			str << '#' << k++ << '\n';
			str << neurons_[i][j].printWeights();
			str << '\n' << '\n' << '\n';
		}
	}
	return str.str();
}
