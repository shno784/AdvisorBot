#pragma once

#include "CSVData.h"
#include <vector>
#include <string>
class Utils
{
public:
	Utils();

	//splits up a string depending on the separator and returns a vector of strings
	static std::vector<std::string> tokenise(const std::string& csvLine, char separator);
	//returns minimum price
	static double minPrice(std::vector<CSVData> data);
	//returns maximum price
	static double maxPrice(std::vector<CSVData> data);
	//returns the total price over set amount of timesteps
	static double totPrice(std::vector<CSVData> data);
	//returns the total amount over set amount of timesteps
	static double totAmount(std::vector<CSVData> data);
	//Sorts maps by value and returns them in ascending order
	static bool sortByVal(const std::pair<std::string, double>& a, const std::pair<std::string, double>& b);

	bool checkDataType(std::string csvType);
};

