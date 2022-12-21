#pragma once
#include <string>

enum class CSVDataType {bid, ask, unknown};
class CSVData {
public:
	CSVData(double _price,
			double _amount,
			std::string _timestamp,
			std::string _product,
			CSVDataType _csvType);

	static CSVDataType stringToCSVDataType(const std::string& s);

	double price;
	double amount;
	std::string timestamp;
	std::string product;
	CSVDataType csvType;
};