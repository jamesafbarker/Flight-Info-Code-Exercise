#include "Database.h"
#include <iostream>
#include <fstream> 
#include <FlightInfoData.h>

/// @brief Constructor for Database object
Database::Database()
{
    m_running = true;
    db_thread = std::thread(&Database::databaseWorker, this);
};

/// @brief Destructor for Database object
Database::~Database()
{
    m_running = false;
    cv.notify_all(); // Notify the worker thread to stop
    if (db_thread.joinable()) {
        db_thread.join();
    }
};

/// @brief Add Flight Information to the database
/// @param info Fight Information struct
void Database::insertInfo(FlightInfoData info) {
    std::lock_guard<std::mutex> lock(queueMutex);
    dbQueue.push(info);
    cv.notify_one(); // Notify the worker thread
}

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

/**
* @brief Worker thread to handle database operations.
*/
void Database::databaseWorker()
{
    while (m_running || !dbQueue.empty()) {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [this] { return !dbQueue.empty() || !m_running; });

        while (!dbQueue.empty()) {
            FlightInfoData data = dbQueue.front();
            dbQueue.pop();
            lock.unlock();
            addInfo(data);
            lock.lock();
        }
    }
};

/// @brief Checks size of database
/// @return True if is empty
bool Database::isEmpty() {
    return flightInfos.empty();
};