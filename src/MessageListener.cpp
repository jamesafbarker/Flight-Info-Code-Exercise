#include "Message.h"
#include "MessageListener.h"
#include "PayloadParser.h"

/// @brief Constructor
MessageListener::MessageListener(ICommunicationProtocol* protocol)
: m_running(false)
, m_commProtocol(protocol)
{
    // Register processors
    m_bufferHandler.registerParser<BinaryPayloadParser>(1);
};

/// @brief Destructor
MessageListener::~MessageListener()
{
    stop();
};

/**
* \brief Starts the message listener 
* @return Success of listener status
*/
bool MessageListener::start()
{
    if (!m_commProtocol->startProtocol())
        return false;
    m_running = true;
    m_listenThread = std::thread(&MessageListener::listen, this);
    m_dbThread = std::thread(&MessageListener::databaseWorker, this);
    return true;
};

/*
* @brief Stops the message listener
*/
void MessageListener::stop()
{
    m_running = false;
    cv.notify_all();
    if (m_listenThread.joinable())
        m_listenThread.join();
    if (m_dbThread.joinable())
        m_dbThread.join();
    m_commProtocol->stopProtocol();
};

/**
* @brief Main looping function for listen thread
*/
void MessageListener::listen() 
{
    while (m_running) {
        std::vector<char> message = m_commProtocol->receive();
        if (!message.empty()){
            m_buffer.insert(m_buffer.end(), message.begin(), message.end());
            processBuffer();
        }
    }
};

/**
 * @brief Main looping function for listen thread
 */
void MessageListener::processBuffer()
{
    while (!m_buffer.empty()) 
    {
        // Todo: Extract from message the message size
        int payloadLength = 12;
        size_t messageSize = 13 + payloadLength;
        
        if (m_buffer.size() < messageSize) {
            return; // Wait until full message is received
        }
        std::vector<char> completeMessage(m_buffer.begin(), m_buffer.begin() + messageSize);
        
        // Remove complete message
        m_buffer.erase(m_buffer.begin(), m_buffer.begin() + messageSize);

        FlightInfoData result;
        bool success = m_bufferHandler.process(completeMessage, result);

        if (success){
            std::cout << "Flight Information Data received. Adding to Database...\n";
            std::lock_guard<std::mutex> lock(queueMutex);
            dbQueue.push(result);
        } else {
            std::cout << "Invalid message received.\n";
            m_buffer.clear();
        }
    }
};

/**
* @brief Worker thread to handle database operations.
*/
void MessageListener::databaseWorker()
{
    while (m_running || !dbQueue.empty()) {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [this] { return !dbQueue.empty() || !m_running; });

        while (!dbQueue.empty()) {
            FlightInfoData data = dbQueue.front();
            dbQueue.pop();
            lock.unlock();

            // Save the result to the database (file)
            m_database.addInfo(data);
            lock.lock();
        }
    }
};