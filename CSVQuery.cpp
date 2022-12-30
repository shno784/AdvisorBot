#include "CSVQuery.h"
#include "CSVData.h"
#include "CSVReader.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <cmath>


CSVQuery::CSVQuery(std::string filename) {
	CSVReader::readCSV(filename);
};

std::vector<std::string> CSVQuery::tokenise(const std::string& csvLine, char separator) {
	std::vector<std::string> tokens;

	signed int start, end;
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

std::vector<std::string> CSVQuery::getProducts(std::string product) {
	//Declare csvreader object
	CSVReader data;
	std::vector<std::string> products;
	std::map<std::string, bool> prodMap;

	//Find the products and put them in the Map
	for (CSVData& d : data.data) {
		
		if (product == "all") {
			prodMap[d.product] = true;
		}
		/*Check if the product is equal to the one entered
		by the user*/
		else if(d.product == product)
		{
			prodMap[d.product] = true;
		}	
	};
	/*Push only the first part of the map
	Which contains the products to a vector*/
	for (auto const& d : prodMap) {
		products.push_back(d.first);
		
	}
	return products;
};

std::string CSVQuery::getEarliestTime()
{	
	//Declare csvreader object
	CSVReader data;
	std::string currentTime = data.currentTime;
	
	return currentTime;
};


std::string CSVQuery::getNextTimeStep(std::string& time) {
	CSVReader data;

	try
	{
		/*Get each line based on the last timestep
		that is pushed into the nexttimestep vector in CSVReader class*/
		data.getLine(data.nextTimestep);
	}
	catch (const std::exception&)
	{

	}

	std::string next_timestamp = "";
	for (auto& d : data.temps)
	{
		if (d > time)
		{
			next_timestamp = d;
			break;
		}
	}
	if (next_timestamp == "")
	{
		next_timestamp = data.temps[0];
	}
	
	return next_timestamp;
};

std::vector<CSVData> CSVQuery::getData(	CSVDataType type, std::string product, std::string timestamp) {
	//Declare csvreader object
	CSVReader data;
	std::vector<CSVData> data_filters;
	//Traverse through the CSV file
	for (const CSVData& d : data.data) {

		//If the values match, push the matches into data_filters
		if (d.csvType == type &&
			d.product == product &&
			d.timestamp == timestamp) {
			data_filters.push_back(d);
		}
	}

	return data_filters;
};

double CSVQuery::minPrice(std::vector<CSVData> data) {
	double min = data[0].price;

	/*Checks if the price in the data is 
	smaller than the min price*/
	for (const CSVData& d : data) {
		if (d.price < min) {
			min = d.price;
		}
	}
	//Convert float to string to get lower values like "1e-08"
	std::string placeholder = std::to_string(min);
	//Convert it back to a float to extract the exact value
	min = std::stof(placeholder);

	return min;
};

double CSVQuery::maxPrice(std::vector<CSVData> data) {
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

double CSVQuery::totPrice(std::vector<CSVData> data) {
	double total = 0;

		//Find all the prices in a timestep
		for (const CSVData& d : data) {
			total += d.price;
		}
		return total;
};