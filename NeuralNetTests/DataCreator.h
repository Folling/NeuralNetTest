#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <random>

#include "helpers.h"

class DataCreator
{
public:
	DataCreator() = delete;
	explicit DataCreator(std::string path);
	~DataCreator();
public:
	void createMultiplicationDataset(size_t amount);
private:
	std::string filepath;
	std::ofstream writer;
};

#undef min
#undef max

inline int rd() {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> dis(-15000, 15000);
	return dis(gen);
}
