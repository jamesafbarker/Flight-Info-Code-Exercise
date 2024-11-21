#include "Database.h"
#include <iostream>
#include <fstream> 
#include <FlightInfoData.h>

/// @brief Constructor for Database object
Database::Database()
{

};

/// @brief Destructor for Database object
Database::~Database()
{
    save("~/Documents/code/BurannaCode/build/sample.txt");
};

void Database::addInfo(FlightInfoData info)
{
    flightInfos.insert(std::pair<std::string, FlightInfoData>(info.getDestination(), info));
}

/// @brief Returns Flight Information 
/// @param flightName : Name of Flight Destination
/// @return Flight information 
FlightInfoData Database::getInfo(std::string flightName){
    return flightInfos.at(flightName);
};

/// @brief Saves local database to file (txt)
/// @return Success of save to database
bool Database::save(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return false;
    }
    // Todo: Save to file
    return true;
}