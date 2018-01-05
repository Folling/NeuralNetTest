#include "Net.h"

Net::Net(Topology t, activationFunctionFlag f):
	topology(t),
	function(f) {

	using namespace std::chrono;
	using hrc = high_resolution_clock;

	hrc c;

	std::cout << "Initialising Net...\n";
	auto start = c.now();

	assert(t.size() >= 3);

	std::cout << "Initialising Layers using topology: [";
	std::copy(t.begin(), t.end(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << '\b';
	std::cout << "]...\n";

	// initialise layers
	for (size_t l = 0; l < t.size(); l++) {
		layers.emplace_back(Layer{});
		// fill layers with neurons, the topology specifies how many neurons are needed for each layer
		size_t amountOutputs = (l == t.size() - 1) ? 0 : t[l + 1];
		for (size_t i = 0; i <= t[l]; i++) {			
			layers.at(l).emplace_back(Neuron{ i, amountOutputs });
		}
		layers.back().back().value = 1.0;
	}

	auto end = c.now();
	std::cout << "Process finished within "
		<< duration_cast<milliseconds>(end - start).count()
		<< " milliseconds...\n";
	std::cout << "Press any key to continue...\n";
	getchar();
	cls();
}

void Net::feedForward(Values input) {
	assert(input.size() == layers.front().size() - 1);

	for (size_t v = 0; v < input.size(); v++) {
		layers.front().at(v).value = input.at(v);
	}

	for(size_t l = 1; l < layers.size(); l++) {
		Layer& prev = layers.at(l-1);
		for(size_t n = 0; n < layers.at(l).size() - 1; n++) {			
			layers.at(l).at(n).feedForward(this->function, prev);
		}
	}
}

void Net::backProp(Values target) {
	iterationCount++;
	Layer& outputLayer = layers.back();

	error = 0.0;

	assert(target.size() == outputLayer.size() - 1);

	for (size_t n = 0; n < outputLayer.size() - 1; n++) {
		double delta = (target.at(n) - outputLayer.at(n).value);
		error += delta*delta;
	}

	error /= outputLayer.size() - 1;
	error = sqrt(error);

	recentError =
		(recentError * smoothingFactor + error)
		/ (smoothingFactor + 1.0);

	for(size_t n = 0; n < outputLayer.size() - 1; n++) {
		outputLayer.at(n).calcOutputGradients(this->function, target[n]);
	}

	for(size_t l = layers.size() - 2; l > 0; l--) {
		Layer& current = layers.at(l);
		const Layer& next = layers.at(l + 1);
		for(size_t n = 0; n < current.size(); n++) {
			current.at(n).calcHiddenGradients(this->function, next);
		}
	}

	for (size_t layerNum = layers.size() - 1; layerNum > 0; layerNum--)
	{
		Layer& current = layers.at(layerNum);
		Layer& prev = layers.at(layerNum - 1);

		for (size_t n = 0; n < current.size() - 1; n++)
		{
			current.at(n).updateWeights(prev);
		}
	}
}
