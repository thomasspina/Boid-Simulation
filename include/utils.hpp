#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <array>

namespace vec2 {
    // pre-calculated cosine values for 4 directions (in radians)
    constexpr std::array<float, 4> cos4Directions = {
        1.0f,                 // cos(0°)
        0.0f,                 // cos(90°)
        -1.0f,                // cos(180°)
        0.0f,                 // cos(270°)
    };

    // pre-calculated sine values for 4 directions (in radians)
    constexpr std::array<float, 4> sin4Directions = {
        0.0f,                 // sin(0°)
        1.0f,                 // sin(90°)
        0.0f,                 // sin(180°)
        -1.0f,                // sin(270°)
    };


    float angleRadians(const sf::Vector2f& vec);

    float angleDegrees(const sf::Vector2f& vec);

    sf::Vector2f vecFromRadian(const float rads);

    sf::Vector2f vecFromDegree(const float deg);

    float distanceBetweenPoints(const sf::Vector2f& v1, const sf::Vector2f& v2);

    float getMagnitude(const sf::Vector2f& vec);

    sf::Vector2f normalize(const sf::Vector2f& vec);

    float centroid(float p1, float p2, float p3);
}

namespace colour {
    sf::Color HexToColour(uint32_t hexValue);
}
