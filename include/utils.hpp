#pragma once

#include <SFML/Graphics.hpp>


namespace vec2 {
    float angleRadians(const sf::Vector2f& vec);

    float angleDegrees(const sf::Vector2f& vec);

    sf::Vector2f vecFromRadian(const float rads);

    sf::Vector2f vecFromDegree(const float deg);

    float distanceFormula(float x1, float x2, float y1, float y2);

    float distanceBetweenPoints(const sf::Vector2f& v1, const sf::Vector2f& v2);

}
