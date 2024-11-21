#ifndef DATABASE_H
#define DATABASE_H
///
/// \brief DatabaseManager handles the database 
///

#include <vector>
#include <map>
#include <string>

#include <FlightInfoData.h>

class Database {

public:
    /// @brief Constructor
    Database();

    /// @brief Deconstructor of Database object
    ~Database();

    /// @brief Add Flight Information to the database
    /// @param info Fight Information struct
    void addInfo(FlightInfoData info);

    /// @brief Returns most recent flight information for a flight with a certain name/id
    /// @param flightName Name of flight
    /// @return Flight Information data
    FlightInfoData getInfo(std::string flightName);

private:
    /// @brief Saves the database to file
    /// @return Success of database save
    bool save(const std::string& filename) const;

private:
    /// @brief Local flight information
    std::map<std::string, FlightInfoData> flightInfos;
};

#endif // DATABASE_H