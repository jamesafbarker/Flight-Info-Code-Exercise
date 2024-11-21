#ifndef PAYLOADPARSER_H
#define PAYLOADPARSER_H
///
/// \brief Payload Parser
///

#include <string>
#include <vector>

#include <cstdint>
#include <cstring>
#include <iomanip>

#include "Database.h"
#include "FlightInfoData.h"

/**
 * @brief Abstract class for parsing raw payload
 */
class AbstractPayloadParser 
{

    public:
        // Constructor
        AbstractPayloadParser() = default;
        // Destructor
        ~AbstractPayloadParser() = default;
        
        /**
         * @brief Parses the payload.
         * @param payload The data payload to parse.
         * @param result The result of the parsing.
         * @return True if parsing was successful, otherwise false.
         */
        virtual bool parse(std::vector<char> payload, FlightInfoData * info);
};


/**
 * @brief Class to parse binary payloads and extract data.
 */
class BinaryPayloadParser : public AbstractPayloadParser 
{

public:
    BinaryPayloadParser() = default;

    /**
     * @brief Parses the payload to extract latitude, longitude, time left, and destination.
     * @param payload The data payload to parse.
     * @param result The result of the parsing.
     * @return True if parsing was successful, otherwise false.
     */
    bool parse(std::vector<char> payload, FlightInfoData * info) override;

private:
    /**
     * @brief Extract a float value from the payload starting at the given offset.
     * @param payload The payload data.
     * @param offset The offset to start extraction.
     * @return The extracted float value.
     */
    float extractFloat(const std::vector<char>& buffer, size_t offset);

    /**
     * @brief Extract a uint16_t value from the payload starting at the given offset.
     * @param payload The payload data.
     * @param offset The offset to start extraction.
     * @return The extracted uint16_t value.
     */
    uint16_t extractUInt16(const std::vector<char>& payload, size_t offset);

    /**
     * @brief Extracts a string value from the payload starting at the given offset.
     * @param payload The payload data.
     * @param offset The offset to start extraction.
     * @param length The length of the string to extract.
     * @return The extracted string value.
     */
    std::string extractString(const std::vector<char>& payload, size_t offset, size_t length);
};

#endif // PAYLOADPARSER_H
