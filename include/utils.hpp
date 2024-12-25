#pragma once

#include <SFML/Graphics.hpp>


namespace vec2 {
    float angleRadians(const sf::Vector2f& vec);

    float angleDegrees(const sf::Vector2f& vec);

    sf::Vector2f vecFromRadian(const float rads);

    sf::Vector2f vecFromDegree(const float deg);

    float distanceBetweenPoints(const sf::Vector2f& v1, const sf::Vector2f& v2);

    float getMagnitude(const sf::Vector2f& vec);

    sf::Vector2f normalize(const sf::Vector2f& vec);
}
