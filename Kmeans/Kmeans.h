#pragma once
#include <type_traits>
#include "Group.h"
#include <math.h>
#include <memory>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <assert.h>

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

	static double euclideanDistance(Point a, Point b) {
		double result = 0;
		int size = a.size();
		for (int i = 0; i < size; i++) {
			result += pow(a[i] - b[i], 2);
		}
		result = sqrt(result);
		return std::move(result);
	}
private:
	std::vector<Group<double>> groups_;
	std::vector<Point> points_;
	std::vector<Point> distances_; //distances x centroids

	int numberOfPoints;
	const int numberOfCentroids;
	void calculateDistances();
	bool regroup();
};