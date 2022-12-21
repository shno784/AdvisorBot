#pragma once
#include <vector>
#include <string>
#include"CSVData.h"
#include "CSVQuery.h"
#include <fstream>
class CSVReader {
public:
	CSVReader();
	static std::vector<CSVData>  readCSV(std::string filename);
	static std::vector<CSVData>  getLine(std::string time);
	static inline std::string a;
	static inline std::vector<CSVData> data;

private:
	
	static CSVData stringsToCSVD(std::vector<std::string> tokens);

	

};