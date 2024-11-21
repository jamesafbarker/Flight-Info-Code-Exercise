#include <gtest/gtest.h>
#include "BufferHandler.h"
#include "PayloadParser.h"
#include "FlightInfoData.h"

// Test fixture for BufferHandler
class BufferHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Register different parsers
        bufferHandler.registerParser<BinaryPayloadParser>(1);
    }

    BufferHandler bufferHandler;
};

// Test case for BinaryProcessor
TEST_F(BufferHandlerTest, ProcessBinaryPayload) {
    std::vector<char> message = {
        0, 0, 0, 0,
        0, 0, 0, 127,     // Checksum
        1,                // Processor identifier
        0, 0, 13,         // Length of payload
        0, 0, 0, 0x42,    // Latitude (0x42 -> 0.0f for simplicity)
        0, 0, 0, 0x42,    // Longitude (0x42 -> 0.0f for simplicity)
        0, 10,            // Time left (10 seconds)
        'N', 'A', 'M'     // Name ("NAM")
    };

    FlightInfoData result;
    bool success = bufferHandler.process(message, result);
    EXPECT_FLOAT_EQ(result.getLatitude(), 32.0);
    EXPECT_FLOAT_EQ(result.getLongitude(), 32.0);
    EXPECT_EQ(result.getETA(), 10);
    EXPECT_EQ(result.getDestination(), "NAM");
}

// Test case for handling incomplete messages
TEST_F(BufferHandlerTest, ProcessIncompleteMessage) {
    // Incomplete message (length defines more bytes than provided)
    std::vector<char> incompleteMessage = {
        0, 0, 0, 0, 0, 0, 0, 127,  // Checksum
        1,  // Parser identifier
        0, 0, 13,  // Length of payload
        0, 0, 0, 0x42,  // Latitude
        0, 0, 0, 0x42,  // Longitude
        0, 10, // Time left (incomplete, missing name bytes)
        'N', 'B'    // Name ("NAM")
    };

    // Process the incomplete message
    FlightInfoData result;
    bool success = bufferHandler.process(incompleteMessage, result);
    EXPECT_FALSE(success);
}

// Main function to run tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
