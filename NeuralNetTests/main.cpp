#include <iostream>
#include <chrono>

#include "helpers.h"
#include "Net.h"
#include "TrainingData.h"

int main() {	
	Topology top = { 2, 2, 1 };
	Net net{ top, TANH };
	TrainingData t{ "C:/Users/Folling/Documents/Visual Studio 2017/Projects/NeuralNetTests/NeuralNetTests/Test1.txt" };

	Values input;
	Values targets;
	for (size_t i = 0; i < 100; i++) {
		while (true) {
			if (!t.read_bracketed(input, targets)) break;
			net.feedForward(input);
			net.backProp(targets);
		}
	}

	for (size_t i = 0; i < 100; i++) {
		while (true) {
			if (!t.read_bracketed(input, targets)) break;
			net.feedForward(input);
			net.backProp(targets);
			std::cout << "Expected: " << targets[0] << '\n';
			std::cout << "Got: " << net.layers.back()[0].value << '\n';
			std::cout << "Average Error: " << net.error << '\n';
			getchar();
		}
	}
}
