#include "CSVData.h"

//CSV data object
CSVData::CSVData(double _price,
	double _amount,
	std::string _timestamp,
	std::string _product,
	CSVDataType _csvType)

:	price(_price),
	amount(_amount),
	timestamp(_timestamp),
	product(_product),
	csvType(_csvType)
{

}

//Checks to see which datatype the user entered
CSVDataType CSVData::stringToCSVDataType(const std::string& s) {
	if (s == "ask") {
		return CSVDataType::ask;
	}

	if (s == "bid") {
		return CSVDataType::bid;
	}

	return CSVDataType::unknown;
}