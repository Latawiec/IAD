#pragma once


template<typename T>
static T euclideanDistance(const std::vector<T>& a, const std::vector<T>& b) {
	T result = 0;
	int size = a.size();
	for (int i = 0; i < size; i++) {
		result += pow(a[i] - b[i], 2);
	}
	result = sqrt(result);
	return result;
}