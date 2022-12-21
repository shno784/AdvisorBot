#include "CSVReader.h"
#include <iostream>
#include <fstream>


CSVReader::CSVReader() {

};

//Load and read the CSV file
std::vector<CSVData> CSVReader::readCSV(std::string filename) {
	std::vector<CSVData> data;
	std::string timestamp;
	//Read from file
	std::ifstream csvFile{ filename };
	std::string line;

	if (csvFile.is_open()) {

		std::cout << "File open" << std::endl;
		std::getline(csvFile, line);

		std::vector<std::string> tokenisedLine = CSVQuery::tokenise(line, ',');
		CSVData csvd = stringsToCSVD(tokenisedLine);
		data.push_back(csvd);
		
		
		timestamp = csvd.timestamp;
		std::cout << timestamp << std::endl;
	}
	else {
		std::cout << "file not open" << std::endl;
	}
	
	//Prints the number of entries in the file
	std::cout << "The file has  " << data.size() << " entiries." << std::endl;

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
	catch (const std::exception&)
	{
		std::cout << "Bad float! " << tokens[3] << std::endl;
		std::cout << "Bad float! " << tokens[4] << std::endl;
		throw;
	}

	CSVData csvd{ price,
						amount,
						tokens[0],
						tokens[1],
						CSVData::stringToCSVDataType(tokens[2]) };
						
	return csvd;

};