#include "utils.hpp"

#include <math.h>

float vec2::angleRadians(const sf::Vector2f& vec) {
    return atan2(vec.y, -vec.x);
}

float vec2::angleDegrees(const sf::Vector2f& vec) {
    return angleRadians(vec) * 180.f / (float) M_PI;
}

sf::Vector2f vec2::vecFromRadian(const float rads) {
    return sf::Vector2f(cos(rads), sin(rads));
}

sf::Vector2f vec2::vecFromDegree(const float deg) {
    return vecFromRadian(deg * 180.f / (float) M_PI);
}