#pragma once
#include <vector>
#include <string>
#include"CSVData.h"
#include "CSVQuery.h"

class CSVReader {
public:
	CSVReader();
	static std::vector<CSVData>  readCSV(std::string filename);

private:
	
	static CSVData stringsToCSVD(std::vector<std::string> tokens);
};