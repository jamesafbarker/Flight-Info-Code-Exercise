#ifndef FLIGHTINFODATA_H
#define FLIGHTINFODATA_H

#include <string>
#include <cstdint>

/**
 * @brief Class to represent the extracted Flight Information data from the payload.
 */
class FlightInfoData
{

public:
    /**
     * @brief Set the latitude.
     * @param lat The latitude value to set.
     * @returns true if successfully set.
     */
    bool setLatitude(float lat);

    /**
     * @brief Set the longitude.
     * @param lon The longitude value to set.
     * @returns true if successfully set.
     */
    bool setLongitude(float lon);

    /**
     * @brief Set the time left in seconds.
     * @param time The time left value to set.
     */
    bool setETA(uint16_t time);

    /**
     * @brief Set the destination of the flight.
     * @param dest The destination to set.
     * @returns true if successfully set.
     */
    bool setDestination(const std::string& dest);

    /**
     * @brief Get the latitude to two decimal places.
     * @return The latitude value.
     */
    float getLatitude() const;

    /**
     * @brief Get the longitude.
     * @return The longitude value.
     */
    float getLongitude() const;

    /**
     * @brief Returns the estimated time remaining in seconds.
     * @return The time left value.
     */
    uint16_t getETA() const;

    /**
     * @brief Get the destination name.
     * @return The destination as a string.
     */
    std::string getDestination() const;

private:
    float latitude;
    float longitude;
    uint16_t eta;
    std::string destination;
};

#endif // FLIGHTINFODATA_H
