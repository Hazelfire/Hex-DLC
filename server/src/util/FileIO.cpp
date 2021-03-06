#include "FileIO.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>

std::string FileIO::doubleArrayToString(Array<double> vector)
{
	std::stringstream ss;
	for (int i = 0; i < vector.size(); i++) {
		ss << std::setprecision(std::numeric_limits<double>::max_digits10) << vector[i];
		if (i != vector.size() - 1) {
			ss << ",";
		}
	}

	return ss.str();
	
}

int numCharacterInString(std::string string, char character) {
	int characterCount = 0;

	for (auto stringCharacter : string) {
		if (stringCharacter == character) {
			characterCount++;
		}
	}
	return characterCount;
}

Array<double> FileIO::stringToDoubleArray(std::string string)
{
	std::stringstream ss(string);
	Array<double> doubleArray = Array<double>(numCharacterInString(string, ','));
	std::string line;

	int i = 0;
	while (std::getline(ss, line, ',')) {
		if (!line.empty()) {
			doubleArray[i] = std::stod(line);
			i++;
		}
	}
	return doubleArray;
}

void FileIO::saveWeightsToFile(std::string filename, Array<double> vector) {
	std::ofstream outFile(filename);

	if (outFile.is_open()) {
		outFile << doubleArrayToString(vector);
		outFile.close();
	}

}

std::vector<double> FileIO::readWeightsFromFile(std::string filename) {
	std::vector<double> weights;
	std::ifstream inFile(filename);

	if (inFile.is_open()) {
		std::string line;
		while (std::getline(inFile, line, ',')) {
			if (!line.empty()) {
				weights.push_back(std::stod(line));
			}
		}
	}

	return weights;
}


//Writes to the output stream as well as to log.txt
void FileIO::logPrint(std::string str) {
	std::cout << str;

	std::ofstream outFile;
	outFile.open("log.txt", std::ofstream::out | std::ofstream::app);

	if (outFile.is_open()) {
		outFile << str;
	}
}
