#include "Utils.h"

Utils::Utils() {

};

std::vector<std::string> Utils::tokenise(const std::string& csvLine, char separator) {
	std::vector<std::string> tokens;

	int64_t start, end;
	//find all characters before the separator
	start = csvLine.find_first_not_of(separator);
	std::string token;
	do {
		//end = next 'separator' after start 
		end = csvLine.find_first_of(separator, start);
		if (start == csvLine.length() || start == end) break;

		if (end >= 0) token = csvLine.substr(start, end - start);
		else token = csvLine.substr(start, csvLine.length() - start);

		//Add token to the end of the tokens vector
		tokens.push_back(token);
		//start = end + 1 to move past this token
		start = end + 1;
	} while (end > 0);


	/*Checks if the token size is == 2  and the first word is "help"
	so it knows that we are calling the help cmd function*/
	if (tokens.size() == 2) {
		if (tokens[0] == "help") {
			tokens[0] = "help cmd";
			return tokens;
		}
		else {
			return tokens;
		}
	}
	else {
		return tokens;
	}
};

double Utils::minPrice(std::vector<CSVData> data) {
	double min = data[0].price;

	/*Checks if the price in the data is
	smaller than the min price*/
	for (const CSVData& d : data) {
		if (d.price < min) {
			min = d.price;
		}
	}

	return min;
};

double Utils::maxPrice(std::vector<CSVData> data) {
	double max = data[0].price;

	/*Checks if the price in the data is
	larger than the max price*/
	for (const CSVData& d : data) {
		if (d.price > max) {
			max = d.price;
		}
	}

	return max;
};

double Utils::totPrice(std::vector<CSVData> data) {
	double total = 0;

	//Find all the prices in a timestep
	for (const CSVData& d : data) {
		total += d.price;
	}

	return total;
};

double Utils::totAmount(std::vector<CSVData> data) {
	double total = 0;

	//Find all the prices in a timestep
	for (const CSVData& d : data) {
		total += d.amount;
	}

	return total;
};

bool Utils::sortByVal(const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
	return a.second > b.second;
};

bool Utils::checkDataType(std::string csvType) {
 
	//If the type isn't ask or bid, return false
	CSVDataType type = CSVData::stringToCSVDataType(csvType);
	if (type == CSVDataType::unknown) {
		return false;
	}
	else {
		return true;
	}
};

bool Utils::checkTime(std::string time) {

	//Checks if the string only has letters
	for (char c : time) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	//Checks if the number entered is more than 0
	if (stoi(time) <= 0) {
		return false;
	}

	return true;
};

bool Utils::checkMaxMin(std::string maxMin) {
	//If the type isn't min or max, return false
	CSVMaxMin type = CSVData::stringToCSVMaxMin(maxMin);
	if (type == CSVMaxMin::unknown) {
		return false;
	}
	else {
		return true;
	}
};