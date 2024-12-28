#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <array>

namespace vec2 {
    // pre-calculated cosine values for 8 directions (in radians)
    constexpr std::array<float, 8> cos8Directions = {
        1.0f,                 // cos(0°)
        0.70710689672f,       // cos(45°)
        0.0f,                 // cos(90°)
        -0.70710643456f,      // cos(135°)
        -1.0f,                // cos(180°)
        -0.70710665177f,      // cos(225°)
        0.0f,                 // cos(270°)
        0.70710667951f        // cos(315°)
    };

    // pre-calculated sine values for 8 directions (in radians)
    constexpr std::array<float, 8> sin8Directions = {
        0.0f,                 // sin(0°)
        0.70710666564f,       // sin(45°)
        1.0f,                 // sin(90°)
        0.7071071278f,        // sin(135°)
        0.0f,                 // sin(180°)
        -0.70710691059f,      // sin(225°)
        -1.0f,                // sin(270°)
        -0.70710688285f       // sin(315°)
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
