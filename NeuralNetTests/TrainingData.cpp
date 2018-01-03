#include "TrainingData.h"

TrainingData::TrainingData(const char* path):
	filepath(path)
{

	if (!exists(filepath)) {
		std::cout << "File doesn't exist!\n";
		getchar();
	}

	reader.open(filepath);

	if (!reader.is_open()) {
		std::cout << "Unable to open" << filepath << "...\n";
	}
}

TrainingData::~TrainingData()
{
}

bool TrainingData::read_bracketed(Values& input, Values& targets) {
	//		   FORMAT
	//   INPUT       OUTPUT
	// [1, 2, 3] => [5, 3, 7]

	input.clear();
	targets.clear();	
	
	
	reader.setf(std::ios::skipws);
	std::string line;
	std::getline(reader, line);

	std::stringstream ss{ line };

	char bracket;
	char expens{};
	double value;
	std::string arrow;

	ss >> bracket;

	while(expens != ']') {
		ss >> value;
		ss >> expens;
		input.push_back(value);
	}

	expens = '_';
	ss >> bracket;
	ss >> arrow;
	ss >> bracket;

	while(expens != ']') {
		ss >> value;
		ss >> expens;
		targets.push_back(value);
	}

	if (reader.eof()) {
		reader.seekg(std::ios::beg);
		return false;
	}
	return true;
}
