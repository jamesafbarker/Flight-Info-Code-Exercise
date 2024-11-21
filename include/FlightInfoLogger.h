#ifndef FLIGHTINFOLOGGER_H
#define FLIGHTINFOLOGGER_H

#include <atomic>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread> 
#include <vector>
#include <iostream>
#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "BufferHandler.h"
#include "CommunicationProtocol.h"
#include "Database.h"
#include "MessageListener.h"

/// @brief Message Listener class
class FlightInfoLogger 
{
public:
    FlightInfoLogger(ICommunicationProtocol* protocol);    

    /// @brief Starts the Flight Information logger service
    /// @return True if successfully starts
    bool start();

    /// @brief Stops the Flight Information logger service
    void stop();
    
private:
    Database * db;
    MessageListener * listener;
};

#endif // FLIGHTINFOLOGGER_H