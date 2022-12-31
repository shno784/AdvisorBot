#include "AdvisorMain.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


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
        std::cout << "advisorbot> " << "predict max ETH/BTC bid 10 -> The average ETH/BTC ask price over the last 10 timesteps was 1.0 " << std::endl;
    }
    else if (input == "time") {
        std::cout << "advisorbot> " << "time -> 2020/03/17 17:01:24" << std::endl;
    }
    else if (input == "step") {
        std::cout << "advisorbot> " << "step -> now at 2020/03/17 17:01:30" << std::endl;
    }
    else if (input == "rank") {
        std::cout << "advisorbot> rank ask amount ->\nRank            Product             amount\n" <<
                                                       "1.            ETH/BTC               239\n" <<
                                                       "2.            DOGE/USDT             210" << std::endl;
    }
    else {
        std::cout << "advisorbot> " << "Invalid Command!" << std::endl;
    }
};


void AdvisorMain::prod() {
    std::cout << "advisorbot> "<< "The Products are: " << std::endl;
    
    
    //Get all the products from the get product function
    for (std::string const& p : data.getProducts("all")) {
        //Show all products to the user
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

        //Get the entries that match in the CSVfile
        entries = data.getData(type, p, currentTime);

        //Send entried to the minPrice function to get the minimum price
        minPrice = data.minPrice(entries);
    }
      
    //If the entry is empty, it means the product wasn't found
    if (entries.size() == 0) {
        std::cout << "advisorbot> " << "Product not found! " << std::endl;
        return;
    }
    //Display the result
    std::cout <<"advisorbot> " << "The min " << csvType << " price for " << product << " is " << minPrice << "." << std::endl;
};


void AdvisorMain::max(std::string product, std::string csvType) {

    //Gets the correct datatype based on the user entry
    CSVDataType type = CSVData::stringToCSVDataType(csvType);
    std::vector<CSVData> entries;
    double maxPrice = 0;

    try
    {
        //Get the correct datatype based on the user entry
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

        //Get the entries that match in the CSVfile
        entries = data.getData(type, p, currentTime);
        //Get the max price of the entries
        maxPrice = data.maxPrice(entries);
    }
 
    //If the entry is empty, it means the product wasn't found
    if (entries.size() == 0) {
        std::cout << "advisorbot> Product not found!" << std::endl;
        return;
    }
    //Display the result
    std::cout << "advisorbot> " << "The max " << csvType << " price for " << product << " is " << maxPrice << "." << std::endl;
};


void AdvisorMain::avg(std::string product, std::string csvType, std::string timestep) {

    CSVDataType type;
    int time = 0;
    double total = 0;
    std::vector<CSVData> entries;
    //Store the current time in a temp variable
    std::string tempTime = currentTime;

    try
    {
        //Gets the correct datatype based on the user entry
        type = CSVData::stringToCSVDataType(csvType);
        if (type == CSVDataType::unknown) {
            std::cout << "advisorbot> Incorrect type. Enter bid or ask." << std::endl;
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
        for (char c : timestep) {
            if (!std::isdigit(c)) {
                throw std::exception{};
            }
        }
        //Convert the string to an integer 
        time = std::stoi(timestep);
        //Checks if the string only has letters

    }
    catch (const std::exception&)
    {
        std::cout << "advisorbot> Please enter a valid number!" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < time; i++) {
        //Get all products based on user entry in the current timestep
        for (std::string const& p : data.getProducts(product)) {

            //Get the entries that match in the CSVfile
            entries = data.getData(type, p, currentTime);
            //Add all the bids/ask in the entries
            total += data.totPrice(entries);
        }
        //Get the next timeframe
        currentTime = data.getNextTimeStep(currentTime);
       
    }
    
    //If the entry is empty, it means the product wasn't found
    if (entries.size() == 0) {
               std::cout << "advisorbot> Product not found!" << std::endl;
               return;
           }

    //Display the result
    std::cout<< std::fixed << "advisorbot> The average " << csvType << " price for " << product << " over the last "<<timestep<<" timesteps is " << total / time << "." << std::endl;

    //Go back to the current time
    currentTime = tempTime;
};


void AdvisorMain::predict(std::string maxMin, std::string product, std::string csvType, std::string timestep) {
    CSVDataType type;
    int time = 0;
    std::vector<CSVData> entries;
    double total = 0;
    //Store the current time in a temp variable
    std::string tempTime = currentTime;
    //Declare a pointer variable and set it to null
    double (*totalmaxMin)(std::vector<CSVData>) = NULL;
    //Try to get the valid csv type
    try
    {
        //Gets the correct datatype based on the user entry
        type = CSVData::stringToCSVDataType(csvType);
        if (type == CSVDataType::unknown) {
            throw std::exception{};
        }
    }
    catch (const std::exception&)
    {
        std::cout << "advisorbot> " << "Incorrect type. Enter bid or ask." << std::endl;
        return;
    }
    //Try to turn the string into an integer
    try
    {
        for (char c : timestep) {
            if (!std::isdigit(c)) {
                throw std::exception{};
            }
        }
        /*Convert the string to an integer
        and checks if the conversion is a valid integer*/
        time = std::stoi(timestep);

        /*Check if the user entered min or max 
        and points the variable "totalmaxmin" to the correct function*/
        if (maxMin == "min") {
            totalmaxMin = data.minPrice;
        }
        else if (maxMin == "max") {
            totalmaxMin = data.maxPrice;
        }
        else {
            throw std::exception{};
        }
       
    }
    catch (const std::exception&)
    {
        std::cout << "advisorbot> Invalid syntax"<< std::endl;
        return;
    }
   

    for (unsigned int i = 0; i < time; i++) {

        //Get all products based on user entry in the current timestep
        for (std::string const& p : data.getProducts(product)) {

            //Get the entries that match in the CSVfile
            entries = data.getData(type, p, currentTime);

            total += totalmaxMin(entries);
            
        }
        //Get the next timeframe
        currentTime = data.getNextTimeStep(currentTime);
    }
    //If the entry is empty, it means the product wasn't found
    if (entries.size() == 0) {
        std::cout << "advisorbot> " << "Product not found! " << std::endl;
        return;
    }
    std::cout << "advisorbot> The average " << maxMin << " price over the next " << timestep << " timesteps is " << total / time << "." << std::endl;


    //Go back to the current time
    currentTime = tempTime;
};

void AdvisorMain::rank(std::string csvType, std::string priceAmount) {

    //Get the correct datatype based on the user entry
    CSVDataType type = CSVData::stringToCSVDataType(csvType);
    double total = 0;
    std::map<std::string, double> myMap;
    std::vector<CSVData> entries;
    //Declare a pointer variable and set it to null
    double (*PriceOrAmount)(std::vector<CSVData>) = NULL;
    //Used to rank the products
    unsigned int count = 1;
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

    try
    {
        /*Check if the user entered price or amount
        and points the variable "PriceOrAmount" to the correct function*/
        if (priceAmount == "price") {
            PriceOrAmount = data.totPrice;
        }
        else if (priceAmount == "amount") {
            PriceOrAmount = data.totAmount;
        }
        else {
            throw std::exception{};
        }
    }
    catch (const std::exception&)
    {
        std::cout << "advisorbot> Invalid syntax!" << std::endl;
        return;
    }
    //Get all the products from the get product function
    for (std::string const& p : data.getProducts("all")) {
        //Get the entries that match in the CSVfile
        entries = data.getData(type, p, currentTime);

        total = PriceOrAmount(entries);
        myMap.emplace(p, total);
    }
    std::cout << "advisorbot> Rank of Products in current Timestep are: " << std::endl;
    std::cout << std::endl;
    std::cout << "Rank            Product             " << priceAmount << std::endl;
    std::cout << std::endl;

    /*std::sort(myMap.begin(), myMap.end());*/
    // Print the values in the map
    for (auto i = myMap.begin(); i != myMap.end(); ++i)
    {
        std::cout << count <<"               " << i->first<<"             " << i->second << std::endl;
        count++;
    }
}

void AdvisorMain::time() {
    std::cout << "advisorbot> " << currentTime << std::endl;
};


void AdvisorMain::step() {
    //Sets next timestep
    std::string nextTime = data.getNextTimeStep(currentTime);
 
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
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return help();
        }       
    }
    else if (input.at(0) == "help cmd") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 2) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return helpCmd(input.at(1));
        }      
    }
    else if (input.at(0) == "prod") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return prod();
        }     
    }
    else if (input.at(0) == "max") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 3) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return max(input.at(1), input.at(2));
        }
    }
    else if (input.at(0) == "min") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 3) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return min(input.at(1), input.at(2));
        }
    }
    else if (input.at(0) == "avg") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 4) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return avg(input.at(1), input.at(2), input.at(3));
        }
    }
    else if (input.at(0) == "predict") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 5) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return predict(input.at(1), input.at(2), input.at(3),input.at(4));
        }   
    }
    else if (input.at(0) == "time") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return time();
        }   
    }
    else if (input.at(0) == "step") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 1) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return step();
        }  
    }
    else if (input.at(0) == "exit") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 1) {
            //If he user doesn't enter anything, send an invalid input
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return;
        }
    }
    else if (input.at(0) == "rank") {
        /*Ensure that the size of the input vector matches the exact
        amount of words needed to call and use the function*/
        if (input.size() != 3) {
            std::cout << "advisorbot> " << "Invalid input!" << std::endl;
        }
        else {
            return rank(input.at(1), input.at(2));
        }
    }
    else {
        //If the user doesn't enter the required info, send an invalid input
        std::cout << "advisorbot> " << "Invalid input!" << std::endl;
    }
};
