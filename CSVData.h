#pragma once
#include <string>

enum class CSVDataType {bid, ask, unknown};
enum class CSVMaxMin {max, min, unknown};
class CSVData {
public:
	//CSVData construct
	CSVData(double _price,
			double _amount,
			std::string _timestamp,
			std::string _product,
			CSVDataType _csvType);

	//Checks to see which datatype the user entered
	static CSVDataType stringToCSVDataType(const std::string& s);
	//Checks to see if max or min was entered
	static CSVMaxMin stringToCSVMaxMin(const std::string& s);

	double price;
	double amount;
	std::string timestamp;
	std::string product;
	CSVDataType csvType;
};