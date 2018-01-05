#include "Neuron.h"

// parameter for gradient -> learning rate
double Neuron::eta = 0.01;

// momentum
double Neuron::alpha = 0.5;

Neuron::Neuron(size_t i, size_t amountOutputs) :
	index(i) {
	for(unsigned c = 0; c < amountOutputs; c++) {
		connections.push_back(Connection{randomWeight(0.0, 1.0)});
	}
}

Neuron::~Neuron() {
}

double Neuron::sumContributions(const Layer& next) const {
	double sum = 0.0;

	for(size_t n = 0; n < next.size() - 1; n++) {
		sum += connections.at(n).weight * next[n].gradient;
	}
	return sum;
}

void Neuron::calcHiddenGradients(const activationFunctionFlag f, const Layer& next) {
	double dow = sumContributions(next);
	gradient = dow * activationFunctionDerivative(f, value);
}

void Neuron::calcOutputGradients(const activationFunctionFlag f, double target) {
	double delta = target - value;
	gradient = delta * activationFunctionDerivative(f, value);
}

void Neuron::feedForward(const activationFunctionFlag f, const Layer& prev) {
	double sum = 0.0;

	for(const auto& i : prev) {
		sum += i.value * i.connections.at(index).weight;
	}

	value = activationFunction(f, sum);
}

void Neuron::updateWeights(Layer& prev) {
	for(size_t n = 0; n < prev.size(); n++) {
		Neuron& neuron = prev[n];
		double oldDeltaWeight = neuron.connections.at(index).deltaWeight;
		double newDeltaWeight =
			// Individual input, magnified by the gradient and train rate
			eta
			* neuron.value
			* gradient
			// Also add momentum = a fraction of the previous delta weight
			+ alpha
			* oldDeltaWeight;
		neuron.connections.at(index).deltaWeight = newDeltaWeight;
		neuron.connections.at(index).weight += newDeltaWeight;
	}
}

double Neuron::activationFunction(const activationFunctionFlag f, double val) {

	switch(f) {
		case TANH: {
			return tanh(val);
		}
		case RELU: {
			if(val < 0) return 0;
			else return val;
		}
		case LRELU: {
			if(val < 0) return val * 0.01;
			else return val;
		}
		case ELU: {
			if(val < 0) return pow(e, val) - 1;
			else return val;
		}
		default: return 1 / (1 + pow(e, -val));
	}
}

double Neuron::activationFunctionDerivative(const activationFunctionFlag f, double val) {

	switch(f) {
		case TANH: {
			return 1.0 - (val * val);
		}
		case RELU: {
			if(val < 0) return 0;
			else return 1;
		}
		case LRELU: {
			if(val < 0) return 0.01 * val;
			else return 1;
		}
		case ELU: {
			if(val < 0) return pow(e, val);
			else return 1;
		}
		default: return 1 / (1 + pow(e, -val));
	}
}
