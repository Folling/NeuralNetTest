#include "TrainingData.h"

TrainingData::TrainingData(std::string path):
	filepath(path)
{

	if (!exists(filepath)) {
		std::cout << filepath <<  "doesn't exist!\n";
		getchar();
		return;
	}

	reader.open(filepath);

	if (!reader.is_open()) {
		std::cout << "Unable to open" << filepath << "...\n";
	}
}

TrainingData::~TrainingData()
{
	reader.close();
}

bool TrainingData::readBracketed(Values& input, Values& targets) {
	//		   FORMAT
	//   INPUT       OUTPUT
	// [1, 2, 3] => [5, 3, 7]

	input.clear();
	targets.clear();	
	
	reader.unsetf(std::ios::skipws);
	std::string linePart;
	std::getline(reader, linePart, ']');

	std::stringstream ss{ linePart };

	double value;

	ss.ignore(1); // initial bracket [

	while(ss >> value) {
		input.push_back(value);
		ss.ignore(1);
	}
	ss.clear();

	reader.ignore(3);
	linePart.clear();
	std::getline(reader, linePart, ']');
	ss.str(linePart);
	

	while(ss >> value) {
		targets.push_back(value);
		ss.ignore(1);
	}
	reader.ignore(1);
	if (reader.eof()) {
		reader.clear();
		return false;
	}
	return true;
}

bool TrainingData::readPixels(Values& input, Values& targets) {
	return false;
}
