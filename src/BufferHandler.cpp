#include "BufferHandler.h"

/**
 * @brief Processes the data and stores the result in a FlightInfoData struct.
 * @param data The data to process.
 * @param result The FlightInfoData struct to store the result.
 * @return True if processing was successful, otherwise false.
 */
bool BufferHandler::process(const std::vector<char>& data, FlightInfoData& output)
{
    if (data.size() < 12){
        return false;
    }

    Message message(data);    
    std::vector<char> messageData(data.begin() + 8, data.end());

    if (!validateChecksum(messageData, message.checksum) ||
        message.payload.size() != message.payloadLength)
        return false;

    int identifier = message.version;
    auto it = parsers.find(identifier);
    if (it != parsers.end()) {
        return it->second->parse(message.payload, &output);
    }
    return false;
};

/**
 * @brief Validates the checksum of a message.
 * @param message The message data.
 * @param checksum The provided checksum.
 * @return True if the checksum is valid, otherwise false.
 */
bool BufferHandler::validateChecksum(const std::vector<char>& message, uint64_t checksum)
{
    // Todo: implement function which handles message data and checksum
    return true;
};