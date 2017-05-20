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
	Kmeans(Init init_type, int centroidsNumber, std::string dataPath);
	~Kmeans();

	bool update();
	std::string printGroupedPoints();
	std::string printCentroids();

private:
	std::vector<Kmeans_Group> groups_;
	std::vector<Point> points_;
	std::vector<Point> distances_; //distances x centroids

	int numberOfPoints;
	const int numberOfCentroids;
	void calculateDistances();
	bool regroup();
	int iterations = 0;
};