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
	void createAdditionTestDataset(size_t amount);
	void createAdditionDataset(size_t amount);
private:
	std::string filepath;
	std::ofstream writer;
};

#undef min
#undef max

inline int rd_int() {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> dis(-15000, 15000);
	return dis(gen);
}

inline double rd_float() {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<double> dis(-1, 1);
	return dis(gen);
}
