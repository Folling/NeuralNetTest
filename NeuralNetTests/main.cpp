#include <iostream>

#include "helpers.h"
#include "Net.h"
#include "TrainingData.h"
#include "DataCreator.h"

const std::string resource = "C:/Users/Folling/Documents/Visual Studio 2017/Projects/NeuralNetTests/NeuralNetTests/";

int main() {
	Topology top = { 3, 6, 6, 2 };
	Net net{ top, SIG };
	TrainingData first{ resource + "Test1.txt" };
	Values input;
	Values targets;
	long double sumErr = 0;
	for (int i = 0; i < 100000; i++) {
		if (i % 100) std::cout << i << "th iteration\n";
		while (true) {
			if (!first.readBracketed(input, targets)) break;
			net.feedForward(input);
			net.backProp(targets);
			sumErr += net.error;
		}
	}
	sumErr /= 100'000;
	
	std::cout << "Average error: " << sumErr << '\n';
	getchar();
	cls();
	while (true) {
		std::cout << "Enter 2 numbers and a result :\n";
		double f, s, r;
		std::cin >> f >> s >> r;
		net.feedForward(std::vector<double>{f, s, r});
		bool wrong = f + s != r;
		std::vector<double> res;
		if(wrong) {
			res = { 1.0, 0.0 };
		} else {
			res = { 0.0, 1.0 };
		}
		net.backProp(res);
		auto netFalse = net.layers.back().at(0).value;
		auto netTrue = net.layers.back().at(1).value;
		if (netFalse > netTrue) std::cout << "False\n";
		else std::cout << "True\n";
	}
}
