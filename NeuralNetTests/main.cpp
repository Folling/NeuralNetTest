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
	for (int i = 0; i < 10; i++) {
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
	auto& back = net.layers.back();
	while (true) {
		if (!second.readBracketed(input, targets)) break;		
		net.feedForward(input);
		double error =
			pow(back.at(0).value - targets.at(0),2)
			+ pow(back.at(1).value - targets.at(1), 2);
		error /= 2;
		error = sqrt(error);
		std::cout << "Input: " << input[0] << '+' << input[1] << '=' << input[2] << '\n';
		std::cout << "Expected: " << targets[0] << '|' << targets[1] << '\n';
		std::cout << "Got: " << back.at(0).value << '|' << back.at(1).value << '\n';
		std::cout << "Error: " << error << '\n';
		getchar();
		cls();
	}
}
