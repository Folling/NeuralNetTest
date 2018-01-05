#include <iostream>

#include "helpers.h"
#include "Net.h"
#include "TrainingData.h"
#include "DataCreator.h"
#include <thread>

const std::string resource = "C:/Users/Folling/Documents/Visual Studio 2017/Projects/NeuralNetTests/NeuralNetTests/";

int main() {
	Topology top = { 3,3,3,2 };
	Net net{ top, ELU };
	TrainingData first{ resource + "Test1.txt" };
	TrainingData second{ resource + "Test2.txt" };
	Values input;
	Values targets;
	for (int i = 0; i < 20; i++) {
		while (true) {
			if (!first.readBracketed(input, targets)) break;
			net.feedForward(input);
			net.backProp(targets);
		}
		std::cout << i+1 << "th iteration\n";
		std::cout << "Error: " << net.error << '\n';
	}
	std::cout << net.error << '\n'; 
	getchar();
	cls();
	while(true) {
		if (!second.readBracketed(input, targets)) break;
		net.feedForward(input);
		double error = 
			  net.layers.back().at(0).value - targets.at(0) 
			+ net.layers.back().at(1).value - targets.at(1);
		error /= 2;
		std::cout << "Error: " << error << '\n';
		getchar();
	}
}
