#include "CSVReader.h"
#include <iostream>
#include <fstream>


CSVReader::CSVReader() {

	
};

//Load and read the CSV file
std::vector<CSVData> CSVReader::readCSV(std::string filename) {

	csvFile.open(filename);

	if (csvFile.is_open()) {
		std::cout << "File open 1 " << std::endl;
	}
	else {
		std::cout << "file not open" << std::endl;
	}
	std::string timestamp;
	//Read from file	
	std::string line;
	try
	{
		//Get the first line o the csv file
		std::getline(csvFile, line);
		CSVData csvd = stringsToCSVD(CSVQuery::tokenise(line, ','));
		
		timestamp = csvd.timestamp;
		currentTime = timestamp;

		data.push_back(csvd);

		getLine(timestamp);
	}
	catch (const std::exception&)
	{

	}

	return data;
};

std::vector<CSVData>  CSVReader::getLine(std::string time) {

	std::string line;
	
	if (csvFile.eof()) {
		std::cout << "End of file!" << std::endl;
	}
	while (std::getline(csvFile, line)) {
		try
		{
			CSVData csvd = stringsToCSVD(CSVQuery::tokenise(line, ','));

			if (csvd.timestamp == time) {
				data.push_back(csvd);
			}
			else {

				a = csvd.timestamp;
				break;
			}

		}
		catch (const std::exception&)
		{

		}

	}
	
	std::cout << "File has " << data.size() << std::endl;

	return data;
};

//Converts the csv data vector to Csv data Object
CSVData CSVReader::stringsToCSVD(std::vector<std::string> tokens)
{

	double price, amount;
	if (tokens.size() != 5) {
		std::cout << "Bad line" << std::endl;
		throw std::exception{};
	}

	//Try catch incase the price and amount aren't double
	try
	{
		// we have 5 tokens string to double
		price = std::stod(tokens[3]);
		amount = std::stod(tokens[4]);
	}
	catch (const std::exception)
	{
		std::cout << "Bad float! " << tokens[3] << std::endl;
		std::cout << "Bad float! " << tokens[4] << std::endl;
		throw std::exception{};
	}

	CSVData csvd{ price,
						amount,
						tokens[0],
						tokens[1],
						CSVData::stringToCSVDataType(tokens[2]) };
						
	return csvd;

};