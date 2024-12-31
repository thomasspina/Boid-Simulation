#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <array>
#include <cmath>

namespace vec2 {
    constexpr float pi = 3.14159265358979323846f;
    constexpr float RAD_TO_DEG = 180.f / pi;
    constexpr float DEG_TO_RAD = pi / 180.f;

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
