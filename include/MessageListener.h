#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H

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

/// @brief Message Listener class
class MessageListener 
{
public:
    /// @brief Constructor
    MessageListener(ICommunicationProtocol* protocol,
                    Database * db);

    /// @brief Deconstructor of Message Listener
    ~MessageListener();

    /// @brief Starts the listener
    /// @return Success of listener status
    bool start();

    /// @brief Stops the listener
    void stop();

private:
    /**
    * @brief Main looping function for listen thread
    */
    void listen();

    /**
     * @brief Main looping function for listen thread
     */
    void processBuffer();

private:
    // Message Listener
    std::thread m_listenThread;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::atomic<bool> m_running;    
    std::deque<char> m_buffer;
    
    BufferHandler m_bufferHandler;
    ICommunicationProtocol * m_commProtocol;
    
    // Database
    Database * m_database;
};

#endif // MESSAGELISTENER_H