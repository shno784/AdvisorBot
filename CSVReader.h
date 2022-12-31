#pragma once
#include <vector>
#include <string>
#include"CSVData.h"
#include "Utils.h"
#include <fstream>

class CSVReader {
public:
	CSVReader();
	static std::vector<CSVData>  readCSV(std::string filename);
	static std::vector<CSVData>  getLine(std::string& time);
	static inline std::string nextTimestep;
	static inline std::vector<CSVData> data;
	static inline std::string currentTime;
	static inline std::ifstream csvFile;
	static inline std::vector<std::string> temps;

private:
	
	static CSVData stringsToCSVD(std::vector<std::string> tokens);
	
};