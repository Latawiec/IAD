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
		groups_.push_back(Group<double>(Neuron<double>(points_[distribution(generator)])));
	}

	distances_ = std::vector<std::vector<double>>(numberOfPoints, std::vector<double>(numberOfCentroids));
}

Kmeans::~Kmeans()
{
	
}

bool Kmeans::update()
{
	iterations++;
	calculateDistances();
	return regroup();
}

std::string Kmeans::printGroupedPoints()
{
	std::ostringstream str;
	for (int i = 0; i < numberOfCentroids; i++) {
		str << '#' << i << '\n';
		str << groups_[i].printPoints();
		str << '\n' << '\n';
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
	//std::vector<const Point*> centroidsPositions(numberOfCentroids);
	std::unique_ptr<const Point*[]> centroidsPositions(new const Point*[numberOfCentroids]);

	for (int i = 0; i < numberOfCentroids; i++) {
		centroidsPositions[i] = &(groups_[i].getParentPosition());
	}

	//Calculate distances
	/*for (int i = 0; i < numberOfPoints; ++i) {
		for (int j = 0; j < numberOfCentroids; ++j) {
			distances_[i][j] = euclideanDistance(*centroidsPositions[j], points_[i]);
		}
	}*/

	//Calculate distances... faster
	const int concurrency = std::thread::hardware_concurrency() - 1;
	std::unique_ptr<std::thread[]> threads(new std::thread[concurrency]);
	{
		int i = 0;
		const int k = numberOfPoints / concurrency;
		for (; i < concurrency - 1; i++) {
			threads[i] = std::thread([&centroidsPositions, i, &k](const int& pointsNum, const int& centroidsNum, std::vector<Point>* distances, std::vector<Point>* points) {
				for (int p = 0; p < k; ++p) {
					for (int c = 0; c < centroidsNum; ++c) {
						(*distances)[p+i*k][c] = euclideanDistance(*centroidsPositions[c], (*points)[p+i*k]);
					}
				}
			}, numberOfPoints, numberOfCentroids, &distances_, &points_);
		}

		threads[i] = std::thread([&centroidsPositions, i, &k](const int& pointsNum, const int& centroidsNum, std::vector<Point>* distances, std::vector<Point>* points) {
			for (int p = k*i; p < pointsNum; ++p) {
				for (int c = 0; c < centroidsNum; ++c) {
					(*distances)[p][c] = euclideanDistance(*centroidsPositions[c], (*points)[p]);
				}
			}
		}, numberOfPoints, numberOfCentroids, &distances_, &points_);
	}

	for (int i = 0; i < concurrency; i++) {
		threads[i].join();
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
	for (int i = 0; i < numberOfPoints; i++) {
		int distance = std::distance(distances_[i].begin(), std::min_element(distances_[i].begin(), distances_[i].end()));
		groups_[distance].add(&points_[i]);
	}

	//Change centroids position with new points
	for (Group<double>& g : groups_) {
		result = result || g.updateParentWeights();
	}
	return result;
}
