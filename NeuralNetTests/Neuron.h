#pragma once

#include <iostream>
#include <random>
#include <vector>

using activationFunctionFlag = short;
enum Functions : activationFunctionFlag {
	SIG = 0x0,
	TANH = 0x1,
	RELU = 0x2,
	LRELU = 0x3,
	ELU = 0x4,
};

#define e 2.71828
struct Neuron;


inline double randomWeight(double lowerBound = 0.0, double upperBound = 1.0){
	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(lowerBound, upperBound);
	return dis(gen);
}

struct Connection {
	explicit Connection(double w) {
		weight = w;
	}
	double weight{};
	double deltaWeight{};
};

using Topology = std::vector<size_t>;
using Layer = std::vector<Neuron>;
using Connections = std::vector<Connection>;

struct Neuron
{
public:
	Neuron() = delete;
	explicit Neuron(size_t i, size_t amountOutputs);
	~Neuron();
public:
	double sumContributions(const Layer& next) const;
	void calcHiddenGradients(const activationFunctionFlag f, const Layer& next);
	void calcOutputGradients(const activationFunctionFlag f, double target);
	void feedForward(const activationFunctionFlag f, const Layer& prev);
	void updateWeights(Layer& prev);
public:
	double activationFunction(const activationFunctionFlag f, double val);
	double activationFunctionDerivative(const activationFunctionFlag f, double val);
public:
	size_t index;
	Connections connections;
	double value{};
	static double eta;
	static double alpha;
	double gradient{};
};