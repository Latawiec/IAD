#include "Kmeans.h"



Kmeans::Kmeans(Init init_type, int centroidsNumber, std::string dataPath)
	: numberOfCentroids(centroidsNumber)
{
	std::ifstream file(dataPath);
	assert(file.is_open());

	while (!file.eof()) {
		points_.push_back(Point(2));
		file >> points_.back()[0];
		file >> points_.back()[1];
	}

	for (int i = 0; i<centroidsNumber; ++i) {
		groups_.push_back(Group<double>(Neuron<double>({0, 0})));
	}
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
	bool result = false; // - this is going to tell us wether anything changed in the positions from the last time.
	//Clear current points in each group
	for (Group<double>& g : groups_) {
		g.clearPoints();
	}

	//Choose which point goes where using calculated distances
	for (const std::vector<double>& p : distances_) {
		groups_[std::distance(p.begin(), std::max_element(p.begin(), p.end()))].add(&p);
	}

	//Change centroids position with new points
	for (Group<double>& g : groups_) {
		result = result && g.updateParentWeights();
	}
	return result;
}
