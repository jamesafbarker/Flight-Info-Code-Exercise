#include "Message.h"
#include "MessageListener.h"
#include "PayloadParser.h"

/// @brief Constructor
MessageListener::MessageListener(ICommunicationProtocol* protocol, Database * db)
: m_running(false)
, m_commProtocol(protocol)
, m_database(db)
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
            // Call to database to add data when able to
            m_database->insertInfo(result);
        } else {
            std::cout << "Invalid message received.\n";
            m_buffer.clear();
        }
    }
};
