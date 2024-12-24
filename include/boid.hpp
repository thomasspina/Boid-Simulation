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
    float speed;
public:
    Boid();

    void initiateBoundary();
    const sf::CircleShape& getBoundary() const;
    void setBoundPos(const float x, const float y);

    void setSpeed(float speed);
    float getSpeed() const;

    void setIdNumber(int id);
    int getIdNumber() const;
    float getRadius() const;
    void setRadius(const float radius);

    void update(const sf::Time& deltaTime);
    void setVelocity(const sf::Vector2f& velocity);
    const sf::Vector2f& getVelocity() const;
    bool isWithinBoundary(const sf::Vector2f& neighborVector, const float radius) const;
};
