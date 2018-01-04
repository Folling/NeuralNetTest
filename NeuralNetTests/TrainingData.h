#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

#include "helpers.h"
#include "Net.h"

using str = std::string;

class TrainingData
{
public:
	TrainingData() = delete;
	TrainingData(std::string path);
	~TrainingData();
public:
	bool readBracketed(Values& input, Values& targets);
	bool readPixels(Values& input, Values& targets);
private:
	str filepath;
	std::ifstream reader;
};