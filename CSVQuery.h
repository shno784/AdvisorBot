#pragma once

#include <vector>
#include <string>
#include "CSVReader.h"
#include "CSVData.h"

class CSVQuery
{
public:
	//Construct that reads the csv file for querying
	CSVQuery();

	//splits up a string depending on the separator and returns a vector of strings
	static std::vector<std::string> tokenise(const std::string&, char separator);
	//return vector of all known products
	std::vector<std::string> getProducts(std::string product);
	
	//returns earliest timeframe in the CSV file
	std::string getEarliestTime();

	/*returns next timestamp in the CSV file
	if the function has reached the last timestamp
	Go back to the first timestamp*/
	std::string getNextTime();

	//returns a vector of data according to the sent filters
	std::vector<CSVData> getData(	CSVDataType type,
									std::string product,
									std::string timestamp);

	//returns minimum price
	static double minPrice(std::vector<CSVData> data);
	//returns maximum price
	static double maxPrice(std::vector<CSVData> data);
	//returns the total price over set amount of timesteps
	static double totPrice(std::vector<CSVData> data);


private:
	//Vector based on the CSV file that will be used for querying
	std::vector<CSVData> data;
};

