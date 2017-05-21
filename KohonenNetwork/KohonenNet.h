#pragma once
#include <random>
#include <fstream>
#include <memory>
#include <tuple>
#include "KohonenNeuron.h"
#include "MyMath.h"
#include <algorithm>
#include <cassert>



class KohonenNet
{
	
	public:
		typedef std::vector<double> Point;

		KohonenNet(int neuronsNumber, std::string dataPath);
		~KohonenNet();

		bool update();
		double calculateDistanceFactor(int k);
		std::string printNeurons();

		int getIterations() { return iterations_; }

	private:
		std::random_device generator_;
		std::uniform_int_distribution<int> distribution_;

		std::vector<std::vector<KohonenNeuron>> neurons_; //dwa wymiary gostek
		std::vector<Point> points_;

		std::vector<std::tuple<KohonenNeuron*, double>> distances_;

		const double teachingFactor = 0.7;
		const double neighbourhoodRange = 3;
		const int numberOfNeurons_;
		double minPotential_ = 0.75;
		int numberOfPoints_;
		int width_;
		int iterations_ = 0;

};

