#include "DataCreator.h"

DataCreator::DataCreator(std::string path)
	:filepath(path)
{
	if(!exists(filepath)) {
		std::cout << filepath << " does not exist.";
		getchar();
		return;
	}
	writer.open(path);
	if(!writer.is_open()) {
		std::cout << "Unable to open " << filepath << '\n';
	}
}


DataCreator::~DataCreator()
{
	writer.close();
}



void DataCreator::createMultiplicationDataset(size_t amount) {
	const char o_bracket = '[';
	const char c_bracket = ']';
	const char comma = ',';
	const std::string arrow = "=>";

	for (int i = 0; i < amount; i++) {
		bool wrong = rd() % 2 == 0;
		int first = rd();
		int second = rd();

		std::string line =
			o_bracket
			+ std::to_string(first)
			+ comma
			+ std::to_string(second)
			+ comma
			+ std::to_string(wrong ? rd() : first + second)
			+ c_bracket
			+ arrow
			+ o_bracket
			+ std::to_string(wrong ? 1.0 : 0.0)
			+ comma
			+ std::to_string(wrong? 0.0 : 1.0)
			+ c_bracket
			+ '\n';

		writer << line;
	}
}
