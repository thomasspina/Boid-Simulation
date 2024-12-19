#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Boid : public sf::CircleShape {
private:
    sf::Vector2f velocity = {0.f, 0.f};
    sf::CircleShape boundary;
public:
    Boid();
    void initiateBoundary();
    sf::CircleShape getBoundary();
    void setBoundPos(const float x, const float y);
    void update(const sf::Time& deltaTime);
    void setVelocity(const sf::Vector2f& velocity);
    bool isWithinBoundary(sf::Vector2f& neighborVector);
};
