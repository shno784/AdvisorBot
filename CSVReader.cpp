#include "CSVReader.h"
#include <iostream>

CSVReader::CSVReader() {
	
};

std::vector<CSVData> CSVReader::readCSV(std::string filename) {

	csvFile.open(filename);

	if (!csvFile.is_open()) {
		std::cout << "Error opening file " << std::endl;
	}


	//Read from file	
	std::string line;
	try
	{
		//Get the first line o the csv file
		std::getline(csvFile, line);
		CSVData csvd = stringsToCSVD(Utils::tokenise(line, ','));

		timestepVec.push_back(csvd.timestamp);
		nextTimestamp = csvd.timestamp;
		currentTime = csvd.timestamp;

		data.push_back(csvd);

		getLine(csvd.timestamp);
	}
	catch (const std::exception&)
	{

	}
	
	return data;
};

std::vector<CSVData>  CSVReader::getLine(std::string& time) {

	std::string line;
	
	//If the File is good, run the code inside, if not close the file
	if (csvFile.good()) {
		//Get all lines
		while (std::getline(csvFile, line)) {
			try
			{
				CSVData csvd = stringsToCSVD(Utils::tokenise(line, ','));
				/*If the timestamp for the line being read is the same as the timestamp entered
				push it back to the data vector*/
				if (csvd.timestamp == time) {
					data.push_back(csvd);
				}
				else {
					//Grabs the first line that isn't equal to the time to store for later
					timestepVec.push_back(csvd.timestamp);
					nextTimestamp = csvd.timestamp;
					break;
				}

			}
			catch (const std::exception&)
			{

			}

		}
	}
	else {
		csvFile.close();
	}
	return data;
};

//Converts the csv data vector to Csv data Object
CSVData CSVReader::stringsToCSVD(std::vector<std::string> tokens)
{

	double price, amount;
	if (tokens.size() != 5) {
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
		throw std::exception{};
	}

	CSVData csvd{ price,
						amount,
						tokens[0],
						tokens[1],
						CSVData::stringToCSVDataType(tokens[2]) };
						
	return csvd;

};