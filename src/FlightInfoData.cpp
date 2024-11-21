#include "FlightInfoData.h"
#include <iostream>

/**
 * @brief Set the latitude.
 * @param lat The latitude value to set.
 * @returns true if successfully set.
 */
bool FlightInfoData::setLatitude(float lat) {
    if (lat < -90.0 || lat > 90.0) {
        std::cerr <<  "Invalid Latitude; must be between -90 and 90 degrees";
        return false;
    }
    latitude = lat;
    return true;
}

/**
 * @brief Set the longitude.
 * @param lon The longitude value to set.
 * @returns true if successfully set.
 */
bool FlightInfoData::setLongitude(float lon) {
    if (lon < -180.0 || lon > 180.0) {
        std::cerr << "Invalid Longitude; must be between -180 and 180 degrees";
        return false;
    }
    longitude = lon;
    return true;
}

/**
 * @brief Set the time left in seconds.
 * @param time The time left value to set.
 */
bool FlightInfoData::setETA(uint16_t time) {
    eta = time;
    return true;
}

/**
 * @brief Set the destination of the flight.
 * @param dest The destination to set.
 * @returns true if successfully set.
 */
bool FlightInfoData::setDestination(const std::string& dest) {
    if (dest.length() != 3) {
        std::cerr << "Invalid Destination name; must be exactly 3 characters long";
        return false;
    }
    destination = dest;
    return true;
}

/**
 * @brief Get the latitude to two decimal places.
 * @return The latitude value.
 */
float FlightInfoData::getLatitude() const {
    return latitude;
}

/**
 * @brief Get the longitude.
 * @return The longitude value.
 */
float FlightInfoData::getLongitude() const {
    return longitude;
}

/**
 * @brief Returns the estimated time remaining in seconds.
 * @return The time left value.
 */
uint16_t FlightInfoData::getETA() const {
    return eta;
}

/**
 * @brief Get the destination name.
 * @return The destination as a string.
 */
std::string FlightInfoData::getDestination() const {
    return destination;
}