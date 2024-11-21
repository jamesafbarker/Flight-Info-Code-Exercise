#ifndef BUFFERHANDLER_H
#define BUFFERHANDLER_H

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include "Message.h"
#include "PayloadParser.h"

/**
 * @brief Wrapper class for payload parser.
 * @tparam Parser The parser type.
 */
template <typename Parser>
class PayloadParserWrapper : public AbstractPayloadParser
{
public:
    /**
     * @brief Parses the payload using the specified parser.
     * @param payload The data payload to parse.
     * @param result The result struct of the parsing.
     * @return True if parsing was successful, otherwise false.
     */
    bool parse(std::vector<char> payload, FlightInfoData * info) override {
        Parser processor;
        return processor.parse(payload, info);
    };
};

// Class to handle buffer and process messages
class BufferHandler 
{
public:

    /**
     * @brief Registers a parser with a specific identifier.
     * @tparam Parser The parser type.
     * @param identifier The identifier for the parser.
     */
    template <typename Parser>
    void registerParser(int identifier) {
        parsers[identifier] = std::make_unique<PayloadParserWrapper<Parser>>();
    };

    /**
     * @brief Processes the data and stores the result in a FlightInfoData struct.
     * @param data The data to process.
     * @param result The FlightInfoData struct to store the result.
     * @return True if processing was successful, otherwise false.
     */
    bool process(const std::vector<char>& data, FlightInfoData& output);

private:
    /**
     * @brief Validates the checksum of a message.
     * @param message The message data.
     * @param checksum The provided checksum.
     * @return True if the checksum is valid, otherwise false.
     */
    bool validateChecksum(const std::vector<char>& message, uint64_t checksum);

private:
    std::map<int, std::unique_ptr<AbstractPayloadParser>> parsers; // Map of parsers
};

#endif // BufferHandler