#pragma once

#include <iostream> // TODO remove

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Boid : public sf::ConvexShape {
private:
    sf::Vector2f velocity = {0.f, 0.f};
    sf::CircleShape boundary;
    int idNumber;
public:
    Boid();

    void initiateBoundary();
    sf::CircleShape getBoundary();
    void setBoundPos(const float x, const float y);

    void setIdNumber(int id);
    int getIdNumber();

    void update(const sf::Time& deltaTime);
    void setVelocity(const sf::Vector2f& velocity);
    sf::Vector2f& getVelocity();
    bool isWithinBoundary(const sf::Vector2f& neighborVector, float radius);
};
