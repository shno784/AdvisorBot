#pragma once
#include <vector>
#include <string>
#include"CSVData.h"
#include "Utils.h"
#include <fstream>

class CSVReader {
public:
	CSVReader();
	//Open csv file and get first line from the file
	static std::vector<CSVData>  readCSV(std::string filename);
	//Get all lines in a given timeframe
	static std::vector<CSVData>  getLine(std::string& time);
	//String to hold the next timestamp to get the other lines in the file
	static inline std::string nextTimestamp;
	//CSV data
	static inline std::vector<CSVData> data;
	//Current time
	static inline std::string currentTime;
	//Store the times in a vector to change the time
	static inline std::vector<std::string> timestepVec;

private:
	//Convert strings to CSV data
	static CSVData stringsToCSVD(std::vector<std::string> tokens);
	//Access the csvFile anywhere in the class
	static inline std::ifstream csvFile;
};