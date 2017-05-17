#pragma once
#include "Neuron.h"
#include <deque>

template<typename T>
class Group
{

public:
	typedef std::vector<T> Point;

	Group(Neuron<T>& parent) : parent_(parent) {}
	Group(Neuron<T>&& parent) : parent_(std::move(parent)) {}
	virtual ~Group() {}

	constexpr const Neuron<T>& getParent()const { return parent_ }
	constexpr const std::vector<Point>& getGroup()const { return points_ }
	const Point& getParentPosition()const { return parent_.getWeights(); }
	void add(const Point* point) { points_.push_back(point); }
	void clearPoints() { points_.clear(); }
	int getGroupSize()const { return points_.size() }
	std::string printParent()const { return parent_.printWeights(); }
	std::string printPoints()const {
		std::ostringstream str;
		for (const Point* p : points_) {
			for (const T val : *p) {
				str << val << '\t';
			}
			str << '\n';
		}
		return str.str();
	}

	bool updateParentWeights() {	//Returns false if parent hasn't moved at all.
		int dim = parent_.getSize();
		int pointsNumber = points_.size();

		std::vector<T> result(dim);

		for (const Point* point : points_) {
			for (int i = 0; i < dim; i++) {
				result[i] += (*point)[i];
			}
		}

		for (T& val : result) {
			val /= pointsNumber;
		}
		
		for (int i = 0; i < dim; i++) {
			if ( result[i] != parent_.getWeights()[i]) {
				parent_.setWeights(result);
				return true;
			}
		}
		return false;
	}

private:
	Neuron<T> parent_;
	std::deque<const Point*> points_;
};

