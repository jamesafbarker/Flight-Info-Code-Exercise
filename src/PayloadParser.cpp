#include "PayloadParser.h"
#include <iostream>
#include <cstdint>
#include <cstring>
#include <iomanip>

/**
 * @brief Parses the payload.
 * @param payload The data payload to parse.
 * @param result The result of the parsing.
 * @return True if parsing was successful, otherwise false.
 */
bool AbstractPayloadParser::parse(std::vector<char> payload, FlightInfoData * info)
{
    return false;
};

/**
 * @brief Parses the payload to extract latitude, longitude, time left, and destination.
 * @param payload The data payload to parse.
 * @param result The result of the parsing.
 * @return True if parsing was successful, otherwise false.
 */
bool BinaryPayloadParser::parse(std::vector<char> payload, FlightInfoData * info)
{
    if (payload.size() < 13)
        return false;

    // Extracting data from payload
    float latitude = 0.0f;
    float longitude = 0.0f;

    // Assuming big-endian format for floats and integers
    std::memcpy(&latitude, payload.data(), sizeof(float));
    std::memcpy(&longitude, payload.data() + sizeof(float), sizeof(float));

    return (info->setLatitude(latitude) &&
            info->setLongitude(longitude) &&
            info->setETA(extractUInt16(payload, 8)) &&
            info->setDestination(extractString(payload, 10, 3)));
};

/**
 * @brief Extract a float value from the payload starting at the given offset.
 * @param payload The payload data.
 * @param offset The offset to start extraction.
 * @return The extracted float value.
 */
float BinaryPayloadParser::extractFloat(const std::vector<char>& buffer, size_t offset) {
    uint32_t temp = (static_cast<uint8_t>(buffer[offset]) << 24) |
                    (static_cast<uint8_t>(buffer[offset + 1]) << 16) |
                    (static_cast<uint8_t>(buffer[offset + 2]) << 8) |
                    static_cast<uint8_t>(buffer[offset + 3]);
    float value;
    std::memcpy(&value, &temp, sizeof(float));
    return value;
}

/**
 * @brief Extract a uint16_t value from the payload starting at the given offset.
 * @param payload The payload data.
 * @param offset The offset to start extraction.
 * @return The extracted uint16_t value.
 */
uint16_t BinaryPayloadParser::extractUInt16(const std::vector<char>& payload, size_t offset) {
    return (static_cast<uint8_t>(payload[offset]) << 8) |
            static_cast<uint8_t>(payload[offset + 1]);
}

/**
 * @brief Extracts a string value from the payload starting at the given offset.
 * @param payload The payload data.
 * @param offset The offset to start extraction.
 * @param length The length of the string to extract.
 * @return The extracted string value.
 */
std::string BinaryPayloadParser::extractString(const std::vector<char>& payload, size_t offset, size_t length) {
    return std::string(payload.begin() + offset, payload.begin() + offset + length);
}