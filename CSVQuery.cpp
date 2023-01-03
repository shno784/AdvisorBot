#include "CSVQuery.h"
#include "CSVData.h"
#include "CSVReader.h"
#include <algorithm>
#include <iostream>
#include <map>


CSVQuery::CSVQuery(std::string filename) {
	CSVReader::readCSV(filename);
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

std::vector<CSVData> CSVQuery::getData(CSVDataType type, std::string product, std::string timestamp) {
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

std::string CSVQuery::getEarliestTime(){	

	//Declare csvreader object
	CSVReader data;
	std::string currentTime = data.currentTime;
	
	return currentTime;
};

std::string CSVQuery::getNextTimeStep(std::string& time){
	//Declare csvreader object
	CSVReader data;
	std::string next_timestamp = "";
	try
	{
		/*Get each line based on the next timestep*/
		data.getLine(data.nextTimestamp);
	}
	catch (const std::exception&)
	{

	}

	//Get the next time
	for (auto& d : data.timestepVec)
	{
		if (d > time)
		{
			next_timestamp = d;
			break;
		}
	}
	//go back to first time if we have reached the last timestamp
	if (next_timestamp == "")
	{
		next_timestamp = data.timestepVec[0];
	}
	
	return next_timestamp;
};

