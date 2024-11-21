#ifndef DATABASE_H
#define DATABASE_H
///
/// \brief DatabaseManager handles the database 
///

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <iostream>

#include <FlightInfoData.h>

class Database {

public:
    /// @brief Constructor
    Database();

    /// @brief Deconstructor of Database object
    ~Database();

    /// @brief Returns most recent flight information for a flight with a certain name/id
    /// @param flightName Name of flight
    /// @return Flight Information data
    FlightInfoData getInfo(std::string flightName);

    /// @brief Add Flight Information to the database
    /// @param info Fight Information struct
    void insertInfo(FlightInfoData info);

    /// @brief Checks size of database
    /// @return True if is empty
    bool isEmpty();

private:
    /// @brief Saves the database to file
    /// @return Success of database save
    bool save(const std::string& filename) const;

    /// @brief Add Flight Information to the database
    /// @param info Fight Information struct
    void addInfo(FlightInfoData info);

    /**
    * @brief Worker thread to handle database operations.
    */
    void databaseWorker();

private:
    /// @brief Local flight information
    std::map<std::string, FlightInfoData> flightInfos;
    
    std::queue<FlightInfoData> dbQueue; /**< Queue for database operations */
    std::mutex queueMutex; /**< Mutex for synchronizing access to the queue */
    std::condition_variable cv; /**< Condition variable for notifying the worker thread */
    std::thread db_thread; /**< Database worker thread */
    std::atomic<bool> m_running; /**< Atomic flag to control the worker thread */
};

#endif // DATABASE_H