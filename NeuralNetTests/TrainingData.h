#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include "Net.h"

using str = std::string;

class TrainingData
{
public:
	TrainingData() = delete;
	TrainingData(const char* path);
	~TrainingData();
public:
	bool read_bracketed(Values& input, Values& targets);
	bool read_pixels(Values& input, Values& targets);
private:
	str filepath;
	std::ifstream reader;
};

inline bool exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}