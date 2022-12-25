#include "AdvisorMain.h"
#include <iostream>
#include <vector>
#include <string>


AdvisorMain::AdvisorMain() {

};

void AdvisorMain::init() {

    currentTime = data.getEarliestTime();
    std::string input;
    std::vector<std::string> userInput;

    //Commands for user
    std::cout << "advisorbot> " << "Please enter a command, or help for a list of commands.(CASE SENSITIVE)" << std::endl;
    std::cout << "advisorbot> " << "Type 'exit' to Exit the program." << std::endl;

    //Run the while loop while input not equal to exit
    do {
        std::cout << "User> ";
        //Get the input from std::cin and store into input
        std::getline(std::cin, input);
        if (input.size() == 0) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            try
            {
                //Gets the user option and store it in the input vector
                userInput = getUserOption(input);

                //Processes the input and selects the correct function
                processUserOption(userInput);
            }
            catch (const std::exception&)
            {
                throw;
            }
        }
    } while (input != "exit");
};


void AdvisorMain::help() {
    std::cout << "advisorbot> " << "The available commands are: " << std::endl;
    std::cout << "help\nhelp <cmd>\navg\nprod\nmin\nmax\npredict\ntime\nstep" << std::endl;
   
    
};


void AdvisorMain::helpCmd(std::string input) {
    
    if (input == "prod") {
        std::cout << "advisorbot> " << "prod -> ETH/BTC,DOGE/BTC" << std::endl;
    }
    else if (input == "min") {
        std::cout << "advisorbot> " << "min ETH/BTC ask -> The min ask for ETH/BTC is 1.0" << std::endl;
    }
    else if (input == "max") {
        std::cout << "advisorbot> " << "max ETH/BTC ask -> The max ask for ETH/BTC is 2.0" << std::endl;
    }
    else if (input == "avg") {
        std::cout << "advisorbot> " << "avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps" << std::endl;
    }
    else if (input == "predict") {
        std::cout << "advisorbot> " << "predict max ETH/BTC bid -> The average ETH/BTC ask price over the last 10 timesteps was 1.0 " << std::endl;
    }
    else if (input == "time") {
        std::cout << "advisorbot> " << "time -> 2020/03/17 17:01:24" << std::endl;
    }
    else if (input == "step") {
        std::cout << "advisorbot> " << "step -> now at 2020/03/17 17:01:30" << std::endl;
    }
    else {
        std::cout << "advisorbot> " << "Invalid Command!" << std::endl;
    }
};


void AdvisorMain::prod() {
    std::cout << "advisorbot> "<< "The Products are: " << std::endl;

    //Get all the products from the get product function
    for (std::string const& p : data.getProducts("all")) {
        
        std::cout << p << std::endl;
    }
};


void AdvisorMain::min(std::string product, std::string csvType) {

    //Gets the correct datatype based on the user entry
    CSVDataType type = CSVData::stringToCSVDataType(csvType);

    double minPrice = 0;
    std::vector<CSVData> entries;
    try
    {
        //Gets the correct datatype based on the user entry
        type = CSVData::stringToCSVDataType(csvType);
        if (type == CSVDataType::unknown) {
            std::cout << "Incorrect type. Enter bid or ask." << std::endl;
            return;
        }
    }
    catch (const std::exception&)
    {
        std::cout << "AdvisorMain::CSVType Error!" << std::endl;
        throw;
    }
    //Get all products based on user entry
    for (std::string const& p : data.getProducts(product)) {
        entries = data.getData(type, p, currentTime);

        
    }
    minPrice = CSVQuery::minPrice(entries);
    //If the entry is empty, it means the product wasn't found
    if (entries.size() == 0) {
        std::cout << "advisorbot> " << "Product not found! " << std::endl;
        return;
    }
    /*Checks if the user entered bid or ask
    and return the correct output*/
    if (csvType == "ask") {
        std::cout << std::fixed << "advisorbot> "<< "The min ask for " << product << " is " << minPrice << std::endl;
    }
    if (csvType == "bid") {
        std::cout << std::fixed << "advisorbot> " << "The min bid for " << product << " is " << minPrice << std::endl;
    }
};


void AdvisorMain::max(std::string product, std::string csvType) {

    //Gets the correct datatype based on the user entry
    CSVDataType type = CSVData::stringToCSVDataType(csvType);
    std::vector<CSVData> entries;
    double maxPrice = 0;

    try
    {
        //Gets the correct datatype based on the user entry
        type = CSVData::stringToCSVDataType(csvType);
        if (type == CSVDataType::unknown) {
            std::cout << "advisorbot> " << "Incorrect type. Enter bid or ask." << std::endl;
            return;
        }
    }
    catch (const std::exception&)
    {
        std::cout << "advisorbot> " << "AdvisorMain::CSVType Error!" << std::endl;
        throw;
    }

    //Get all products based on user entry
    for (std::string const& p : data.getProducts(product)) {

        entries = data.getData(type, p, currentTime);
        
    }
    maxPrice = CSVQuery::maxPrice(entries);
    //If the entry is empty, it means the product wasn't found
    if (entries.size() == 0) {
        std::cout << "advisorbot> " << "Product not found! " << std::endl;
        return;
    }

    if (csvType == "ask") {
        std::cout << std::fixed << "advisorbot> " << "The max ask for " << product << " is " << maxPrice << std::endl;
    }
    if (csvType == "bid") {
        std::cout << std::fixed << "advisorbot> " << "The max bid for " << product << " is " << maxPrice << std::endl;
    }
};


void AdvisorMain::avg(std::string product, std::string csvType, std::string timestep) {

    CSVDataType type;
    int time = 0;
    double avg = 0;
    double total = 0;
    std::vector<CSVData> entries;
    //Store the current time in a temp variable
    std::string tempTime = currentTime;


    try
    {
        //Gets the correct datatype based on the user entry
        type = CSVData::stringToCSVDataType(csvType);
        if (type == CSVDataType::unknown) {
            std::cout << "advisorbot> " << "Incorrect type. Enter bid or ask." << std::endl;
            return;
        }
    }
    catch (const std::exception&)
    {
        std::cout << "AdvisorMain::CSVType Error!" << std::endl;
        throw;
    }

    try
    {
        /*Convert the string to an integer 
        and checks if the conversion is a valid integer*/
        time = std::stoi(timestep);
    }
    catch (const std::exception&)
    {
        std::cout << "advisorbot> " << "Please enter a valid number!" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < time; i++) {

        //Get all products based on user entry in the current timestep
        for (std::string const& p : data.getProducts(product)) {

            entries = data.getData(type, p, currentTime);
            //Add all the bids/ask in the entries
            total += data.totPrice(entries);

        }
        currentTime = data.getNextTime();
        
    }
    //If the entry is empty, it means the product wasn't found
    if (entries.size() == 0) {
               std::cout << "advisorbot> " << "Product not found! " << std::endl;
               return;
           }
    avg = total / time;
    if (csvType == "ask") {
        std::cout << std::fixed << "advisorbot> " << "The average " << product << " ask price over the last " << timestep << " timesteps was " << avg << std::endl;
    }
    if (csvType == "bid") {
        std::cout << std::fixed << "advisorbot> " << "The average " << product << " bid price over the last " << timestep << " timesteps was " << avg << std::endl;
    } 
    //Get back the current time
    currentTime = tempTime;
};


void AdvisorMain::predict() {

};


void AdvisorMain::time() {
    std::cout << "advisorbot> " << currentTime << std::endl;
};


void AdvisorMain::step() {
    //Sets next timestep
    std::string nextTime = data.getNextTime();
 
    std::cout << "advisorbot> " << "Now at "<< nextTime << std::endl;
    //Converts the current time to the next time
    currentTime = nextTime;
};


std::vector<std::string> AdvisorMain::getUserOption(std::string userInput) {

    try
    {
        // Takes the input from the user and puts it into a vector based on white space.
        std::vector<std::string> newInput = CSVQuery::tokenise(userInput, ' ');
        return newInput;
    }
    catch (const std::exception& e)
    {
        std::cout << "AdvisorMain::getUserOption ERROR!! " << std::endl;
        throw;
    }  
};


void AdvisorMain::processUserOption(std::vector<std::string> input) {
    
    if (input.at(0) == "help") {
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return help();
        }       
    }
    else if (input.at(0) == "help cmd") {
        if (input.size() != 2) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return helpCmd(input.at(1));
        }      
    }
    else if (input.at(0) == "prod") {
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return prod();
        }     
    }
    else if (input.at(0) == "max") {
        if (input.size() != 3) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return max(input.at(1), input.at(2));
        }
    }
    else if (input.at(0) == "min") {
        if (input.size() != 3) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return min(input.at(1), input.at(2));
        }
    }
    else if (input.at(0) == "avg") {
        if (input.size() != 4) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return avg(input.at(1), input.at(2), input.at(3));
        }
    }
    else if (input.at(0) == "predict") {
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return predict();
        }   
    }
    else if (input.at(0) == "time") {
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return time();
        }   
    }
    else if (input.at(0) == "step") {
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return step();
        }  
    }
    else if (input.at(0) == "exit") {
        std::cout << input.at(0) << std::endl;
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return;
        }
    }
    else {
        std::cout << "advisorbot> " << "Invalid input!" << std::endl;
    }
};
