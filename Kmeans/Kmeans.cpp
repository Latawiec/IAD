#include "Kmeans.h"



Kmeans::Kmeans(Init init_type, int centroidsNumber, std::string dataPath)
	: numberOfCentroids(centroidsNumber)
{

}


Kmeans::~Kmeans()
{

}

bool Kmeans::update()
{
	calculateDistances();
	return regroup();
}

void Kmeans::calculateDistances()
{
	//Get current positions
	std::vector<const Point*> centroidsPositions(numberOfCentroids);
	for (const Group<double>& g : groups_) {
		centroidsPositions.push_back(&(g.getParentPosition()));
	}
	
	//Calculate distances
	for (int i = 0; i < numberOfPoints; ++i) {
		for (int j = 0; j < numberOfCentroids; ++j) {
			distances_[i][j] = euclideanDistance(*centroidsPositions[j], points_[i]);
		}
	}
}

bool Kmeans::regroup()
{
	//Clear current points in each group
	for (Group<double>& g : groups_) {
		g.clearPoints();
	}

	//Choose which point goes where using calculated distances
	for (const std::vector<double>& p : distances_) {
		groups_[std::distance(p.begin(), std::max_element(p.begin(), p.end()))].add(&p);
	}

	//*******
	return false;
}
