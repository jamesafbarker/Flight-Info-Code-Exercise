/**
* @brief Service that receives flight information and saves data to a database
* @file main.cpp
**/

#include <stdio.h>
#include <iostream>
#include <csignal>

#include "CommunicationProtocol.h"
#include "MessageListener.h"

#include "FlightInfoLogger.h"

FlightInfoLogger* fil = nullptr;

void handleSignal(int signal) 
{
    if (fil) { 
        std::cout << "Signal " << signal << " received. Stopping the service..." << std::endl;
        fil->stop();
    } 
} 

int main(int argc, char ** argv)
{
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

    // Initialise UDP communication
    UPDCommunicationProtocol protocol;
    fil = new FlightInfoLogger(&protocol);
    if (fil->start())
    {
        std::cout << "Started Flight Information Listener service.\n";
        while (true)
            std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
};