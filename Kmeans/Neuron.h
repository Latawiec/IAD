#pragma once
#include <vector>
#include <sstream>

template <typename T>
class Neuron
{
public:
	Neuron(std::initializer_list<T> &&values) : weights_(std::move(values)) {};
	Neuron(std::vector<T> &&values) : weights_(std::move(values)) {};
	Neuron(const std::vector<T> &values) : weights_(values) {};
	virtual	~Neuron() {};

	constexpr const std::vector<T>& getWeights()const { return weights_; };
	void setWeights(const std::vector<T> &values) { weights_ = std::copy(values) };
	std::string printWeights()const {
		std::ostringstream str;
		for (const T& val : weights_) {
			str << val << '\t';
		}
		return str.str();
	}
	int getSize() { return weights_.size() };

private:
	std::vector<T> weights_;
};

