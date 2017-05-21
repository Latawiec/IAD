#include "Kmeans_Group.h"

bool Kmeans_Group::updateParentWeights()
{	
	int pointsNumber = points_.size();
	if (points_.size() == 0) return false;
	int dim = parent_.getSize();

	std::vector<double> result(dim);

	for (const Point* point : points_) {
		for (int i = 0; i < dim; i++) {
			result[i] += (*point)[i];
		}
	}

	for (double& val : result) {
		//assert(pointsNumber != 0);
		val /= pointsNumber;
	}

	for (int i = 0; i < dim; i++) {
		if ((result[i] - parent_.getWeights()[i]) > 0.01f) {
			parent_.setWeights(std::move(result));
			return true;
		}
	}
	return false;
}
