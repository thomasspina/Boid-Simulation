#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <array>

namespace vec2 {    
    // pre-calculated cosine values for 16 directions (in radians)
    constexpr std::array<float, 16> cos16Directions = {
        1.0f,     // cos(0°)
        0.9239f,  // cos(22.5°)
        0.7071f,  // cos(45°)
        0.3827f,  // cos(67.5°)
        0.0f,     // cos(90°)
        -0.3827f, // cos(112.5°)
        -0.7071f, // cos(135°)
        -0.9239f, // cos(157.5°)
        -1.0f,    // cos(180°)
        -0.9239f, // cos(202.5°)
        -0.7071f, // cos(225°)
        -0.3827f, // cos(247.5°)
        0.0f,     // cos(270°)
        0.3827f,  // cos(292.5°)
        0.7071f,  // cos(315°)
        0.9239f   // cos(337.5°)
    };

    // pre-calculated sine values for 16 directions (in radians)
    constexpr std::array<float, 16> sin16Directions = {
        0.0f,     // sin(0°)
        0.3827f,  // sin(22.5°)
        0.7071f,  // sin(45°)
        0.9239f,  // sin(67.5°)
        1.0f,     // sin(90°)
        0.9239f,  // sin(112.5°)
        0.7071f,  // sin(135°)
        0.3827f,  // sin(157.5°)
        0.0f,     // sin(180°)
        -0.3827f, // sin(202.5°)
        -0.7071f, // sin(225°)
        -0.9239f, // sin(247.5°)
        -1.0f,    // sin(270°)
        -0.9239f, // sin(292.5°)
        -0.7071f, // sin(315°)
        -0.3827f  // sin(337.5°)
    };

    constexpr float RAD_TO_DEG = 180.f / M_PI;
    constexpr float DEG_TO_RAD = M_PI / 180.f;

    float angleRadians(const sf::Vector2f& vec);

    float angleDegrees(const sf::Vector2f& vec);

    sf::Vector2f vecFromRadian(const float rads);

    sf::Vector2f vecFromDegree(const float deg);

    float distanceBetweenPoints(const sf::Vector2f& v1, const sf::Vector2f& v2);

    float squaredDistanceBetweenPoints(const sf::Vector2f& v1, const sf::Vector2f& v2);

    float getMagnitude(const sf::Vector2f& vec);

    sf::Vector2f normalize(const sf::Vector2f& vec);

    float centroid(float p1, float p2, float p3);
}

namespace colour {
    sf::Color HexToColour(uint32_t hexValue);
}
