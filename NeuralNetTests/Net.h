#pragma once

#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <iterator>

#include "helpers.h"
#include "Neuron.h"

using Values = std::vector<double>;

class Net {
public:
	Net() = delete;
	explicit Net(Topology t, activationFunctionFlag f);
	~Net() { getchar(); }
public:
	void feedForward(Values input);
	void backProp(Values target);
public:
	std::vector<Layer> layers;
	double error{};
private:
	Topology topology;	
	activationFunctionFlag function;	
	double recentError{};
	const double smoothingFactor{ 100.0 };
};
