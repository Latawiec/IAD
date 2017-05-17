#pragma once
#include "Neuron.h"

template<typename T>
class Group
{
typedef std::vector<T> Point;

public:
	Group(Neuron<T>& parent) : parent_(parent) {};
	Group(Neuron<T>&& parent) : parent_(std::move(parent)) {};
	virtual ~Group() {};

	constexpr const Neuron<T>& getParent()const { return parent_ };
	constexpr const std::vector<Point>& getGroup()const { return points_ };
	void add(const std::vector<Point>& point) { points_.push_back(point) };
	void move(std::vector<Point>& point) { points_.push_back(std::move(point)) };
	void clear() { points_.clear() };

private:
	const Neuron<T>& parent_;
	std::vector<Point> points_;
};

