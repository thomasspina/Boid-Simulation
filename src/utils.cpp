#include "utils.hpp"

#include <math.h>

float vec2::angleRadians(const sf::Vector2f& vec) {
    return atan2(vec.x, -vec.y);
}

float vec2::angleDegrees(const sf::Vector2f& vec) {
    return angleRadians(vec) * 180.f / M_PI;
}

sf::Vector2f vec2::vecFromRadian(const float rads) {
    return sf::Vector2f(cos(rads), sin(rads));
}

sf::Vector2f vec2::vecFromDegree(const float deg) {
    return vecFromRadian(deg * 180.f / M_PI);
}

float vec2::distanceBetweenPoints(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

float vec2::getMagnitude(const sf::Vector2f& vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f vec2::normalize(const sf::Vector2f& vec) {
    float length = getMagnitude(vec);

    return {vec.x / length, vec.y / length};
}

float vec2::centroid(float p1, float p2, float p3) {
    return (p1 + p2 + p3) / 3;
}

sf::Color colour::HexToColour(uint32_t hexValue) {
    return sf::Color(
        (hexValue >> 16) & 0xFF,  // Extract red
        (hexValue >> 8) & 0xFF,   // Extract green
        hexValue & 0xFF          // Extract blue
    );
}
