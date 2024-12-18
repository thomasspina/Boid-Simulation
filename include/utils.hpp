#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>


namespace vec2 {
    float angleRadians(const sf::Vector2f& vec) {
        return atan2(vec.y, -vec.x);
    }

    float angleDegrees(const sf::Vector2f& vec) {
        return angleRadians(vec) * 180 / M_PI;
    }
}