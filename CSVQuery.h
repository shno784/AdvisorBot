#pragma once

#include <vector>
#include <string>
#include "CSVReader.h"
#include "CSVData.h"
#include <algorithm>

class CSVQuery
{
public:
	//Construct that reads the csv file for querying
	CSVQuery(std::string filename);

	//return vector of all known products
	std::vector<std::string> getProducts(std::string product);
	
	//returns earliest timeframe in the CSV file
	std::string getEarliestTime();

	//returns a vector of data according to the sent filters
	std::vector<CSVData> getData(	CSVDataType type,
									std::string product,
									std::string timestamp);

	//Get time for step function
	std::string getNextTimeStep(std::string& time);
private:
	unsigned int i = 0;
};

