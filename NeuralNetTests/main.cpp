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
			cls();
			if (!t.read_bracketed(input, targets)) break;
			net.feedForward(input);
			net.backProp(targets);
			std::cout << "Input: " << input[0] << '|' << input[1] << '\n';
			std::cout << "Expected: " << targets[0] << '\n';
			std::cout << "Got: " << net.layers.back().front().value << '\n';
			std::cout << "Average Error: " << net.error << '\n';

			getchar();

			cls();
			std::cout << "Weights of Net:\n";
			for(auto& i : net.layers) {
				for(auto& n : i) {
					for(auto& c : n.connections) {
						std::cout << c.weight << '\n';
					}
				}
			}


			getchar();
		}
	}
}
