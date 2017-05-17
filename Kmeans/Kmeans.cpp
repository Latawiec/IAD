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
	file.close();

	numberOfPoints = points_.size();

	std::random_device generator;
	std::uniform_int_distribution<int> distribution(0, numberOfPoints-1);

	for (int i = 0; i<centroidsNumber; ++i) {
		groups_.push_back(Group<float>(Neuron<float>(points_[distribution(generator)])));
	}

	distances_ = std::vector<std::vector<float>>(numberOfPoints, std::vector<float>(numberOfCentroids));
}

Kmeans::~Kmeans()
{
	
}

bool Kmeans::update()
{
	calculateDistances();
	return regroup();
}

std::string Kmeans::printGroupedPoints()
{
	std::ostringstream str;
	for (int i = 0; i < numberOfCentroids; i++) {
		str << '#' << i << '\n';
		str << groups_[i].printPoints();
		str << '\n';
	}
	return str.str();
}

std::string Kmeans::printCentroids()
{
	std::ostringstream str;
	for (int i = 0; i < numberOfCentroids; i++) {
		str << '#' << i << '\n';
		str << groups_[i].printParent();
		str << '\n';
	}
	return str.str();
}

void Kmeans::calculateDistances()
{
	//Get current positions
	std::vector<const Point*> centroidsPositions;
	centroidsPositions.reserve(numberOfCentroids);
	for (const Group<float>& g : groups_) {
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
	for (Group<float>& g : groups_) {
		g.clearPoints();
	}

	//Choose which point goes where using calculated distances
	for (const std::vector<float>& p : distances_) {
		groups_[std::distance(p.begin(), std::min_element(p.begin(), p.end()))].add(&p);
	}

	//Change centroids position with new points
	for (Group<float>& g : groups_) {
		result = result || g.updateParentWeights();
	}
	return result;
}
