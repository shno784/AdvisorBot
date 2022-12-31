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
	//Check if the datatype entered is a valid one
	static bool checkDataType(std::string csvType);
	//Check if entered is the correct maxMin type
	static bool checkMaxMin(std::string maxMin);
	//Validate if a correct string was entered to convert to an int and if the string is more than 0
	static bool checkTime(std::string time);
};

