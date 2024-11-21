#include "FlightInfoLogger.h"

/// @brief Constructor for Flight Information Logger
/// @param protocol : Communication protocol class
FlightInfoLogger::FlightInfoLogger(ICommunicationProtocol * protocol) 
: db(new Database())
, listener(new MessageListener(protocol, db))
{
        
};

/// @brief Starts the Flight Information logger service
/// @return True if successfully starts
bool FlightInfoLogger::start(){
    return listener->start();
};

/// @brief Stops the Flight Information logger service
void FlightInfoLogger::stop() {
    listener->stop();
};