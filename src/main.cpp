/**
* @brief Service that receives flight information and saves data to a database
* @file main.cpp
**/

#include <stdio.h>
#include <iostream>
#include <csignal>

#include "CommunicationProtocol.h"
#include "MessageListener.h"

MessageListener* messageListener = nullptr;


void handleSignal(int signal) 
{
    if (messageListener) { 
        std::cout << "Signal " << signal << " received. Stopping the service..." << std::endl;
        messageListener->stop();
    } 
} 

int main(int argc, char ** argv)
{
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

    // Initialise UDP communication
    UPDCommunicationProtocol protocol;
    messageListener = new MessageListener(&protocol);
    if (messageListener->start())
    {
        std::cout << "Started Flight Information Listener service.\n";
        while (true)
            std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
};