#ifndef COMMUNICATIONPROTOCOL_H
#define COMMUNICATIONPROTOCOL_H

#include <vector>

/**
 * @brief Interface for communication protocols.
 */
class ICommunicationProtocol 
{
public:
    virtual ~ICommunicationProtocol() = default;

    /**
     * @brief Start the specific protocol. Implemented by derived classes.
     * @return True if the protocol started successfully, otherwise false.
     */
    virtual bool startProtocol() = 0;

    /**
     * @brief Stop the specific protocol. Implemented by derived classes.
     */
    virtual void stopProtocol() = 0;

    /**
     * @brief Receive data from the protocol.
     * @return Raw data received from the protocol.
     */
    virtual std::vector<char> receive() = 0;
};

/**
 * @brief Class for UPD Communication Protocol receiver
 */
class UPDCommunicationProtocol : public ICommunicationProtocol
{
public:
    /// @brief Constructor for UPD Communication Protocol
    UPDCommunicationProtocol();

    /// @brief Starts the UDP Communication Protocol
    /// @return true if udp is started 
    bool startProtocol() override;

    /// @brief Stops the UDP Communication Protocol
    void stopProtocol() override;

    /// @brief Receives UDP data from communication protocol
    /// @return Raw data from UDP
    std::vector<char> receive() override { return std::vector<char>();};
};

#endif // COMMUNICATIONPROTOCOL_H
