#pragma once
#include <type_traits>
#include "Kmeans_Group.h"
#include "MyMath.h"
#include <math.h>
#include <memory>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <assert.h>
#include <random>
#include <thread>

class Kmeans
{
public:
	typedef std::vector<double> Point;

	enum class Init : unsigned char {
		Forgy,
		RP
	};
	Kmeans(Init init_type, int centroidsNumber, std::string dataPath, int dim=2);
	Kmeans(Init init_type, int centroidsNumber, const std::vector<Point>& data, int dim=2);
	~Kmeans();

	bool update();
	std::string printGroupedPoints();
	std::string printCentroids();
	int getIterations() { return iterations_; }
	std::vector<Point> getCentroidsPositions() { 
		using std::transform;
		std::vector<Point> result(groups_.size());
		transform(groups_.cbegin(), groups_.cend(), result.begin(), [](const Kmeans_Group& g)->Point { return g.getParent().getWeights(); });
		return result;
	}

private:
	std::vector<Kmeans_Group> groups_;
	std::vector<Point> points_;
	std::vector<Point> distances_; //distances x centroids

	void initialize(Init init_type, int centroidsNumber);

	int numberOfPoints;
	const int numberOfCentroids;
	void calculateDistances();
	bool regroup();
	int iterations_ = 0;
};