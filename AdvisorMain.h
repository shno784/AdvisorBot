#pragma once

#include <vector>
#include <string>
#include "CSVData.h"
#include "CSVReader.h"
#include "CSVQuery.h"

class AdvisorMain
{
public:
	AdvisorMain();
	//Starts the Advisorbot
	void init();

private:
	//List all available commands
	void help();
	//Output help for the specified command
	void helpCmd(std::string input);
	// List avaialble products
	void prod();
	//Find minimum bid or ask for product in current time step
	void min(std::string product, std::string csvType);
	//Find maximum bid or ask for product in current time step
	void max(std::string product, std::string csvType);
	//Compute average ask or bid for the sent product over the sent number of time steps
	void avg(std::string product, std::string csvType, std::string timestep);
	//Predict max or min ask or bid for the sent product for the next time step
	void predict(std::string maxMin, std::string product, std::string csvType, std::string timestep);
	//Rank the bid or ask for products by price or amount of that product in a given time
	void rank(std::string csvType, std::string priceAmount);
	//State current time in a dataset, i.e the timeframe we're in
	void time();
	// Move to the next timestep
	void step();
	//Gets the option from the user
	std::vector<std::string> getUserOption(std::string userInput);
	//Decides which function should be called based on user input 
	void processUserOption(std::vector<std::string> input);
	//Object based on the CSV file that will be used for querying
	CSVQuery data{ "C:\\Users\\Joshua\\Downloads\\8-zwpcUsQcOs8KXFLLHDoA_44a269c5c286402492999c4cf79073a4_merklerex_end_topic_5-cw_version_20200601\\merklerex_end_topic_5\\src\\20200601.csv" };





	//String to hold the current time
	std::string currentTime;

};

