#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <vector>
#include <iostream>

struct Message {
    uint64_t checksum;
    int version;
    uint16_t payloadLength;
    std::vector<char> payload;

    // Constructor to parse data
    Message(const std::vector<char>& data) {
        checksum = 0;
        for (int i = 0; i < 8; ++i) {
            checksum = (checksum << 8) | static_cast<uint8_t>(data[i]);
        }
        version = static_cast<int>(data[8]);
        payloadLength = (static_cast<uint8_t>(data[9]) << 16) |
                        (static_cast<uint8_t>(data[10]) << 8) |
                        (static_cast<uint8_t>(data[11]));
        payload = std::vector<char>(data.begin() + 12, data.end());
    }
};

#endif // MESSAGE_H
