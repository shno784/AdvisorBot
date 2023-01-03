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

	//Get the next time in the csv file
	std::string getNextTimeStep(std::string& time);
	//Get the previous time in the csv file
	std::string getPrevTimeStep(std::string& time);
	//Count the number of steps taken
	unsigned int stepCount = 0;
private:
	unsigned int i = 0;
};

