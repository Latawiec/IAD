#pragma once
#include "Neuron.h"
#include <deque>

template<typename T>
class Group
{

public:
	typedef std::vector<T> Point;

	Group(Neuron<T>& parent) : parent_(parent) {};
	Group(Neuron<T>&& parent) : parent_(std::move(parent)) {};
	virtual ~Group() {};

	constexpr const Neuron<T>& getParent()const { return parent_ };
	constexpr const std::vector<Point>& getGroup()const { return points_ };
	const Point& getParentPosition()const { return parent_.getWeights(); };
	void add(const Point* point) { points_.push_back(point); };
	void clearPoints() { points_.clear(); };
	int getGroupSize()const { return points_.size() };

	bool updateParentWeights() {	//Returns false if parent hasn't moved at all.
		int size = parent_.getSize();
		std::vector<T> result(size);
		for (const Point* point : Points) {
			for (int i = 0; i < size; i++) {
				result[i] += (*point)[i];
			}
		}

		for (T& val : result) {
			val /= size;
		}
		
		for (int i = 0; i < size; i++) {
			if (result[i] != parent_[i]) {
				parent_.setWeights(std::move(result));
				return true;
			}
		}
		return false;
	}

private:
	const Neuron<T>& parent_;
	std::deque<const Point*> points_;
};

