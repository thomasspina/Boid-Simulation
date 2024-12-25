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

    void update(const sf::Time& deltaTime);
    bool isWithinBoundary(const sf::Vector2f& neighborVector, const float radius) const;

    // getters
    const sf::CircleShape& getBoundary() const { return this->boundary; }
    float getSpeed() const { return this->speed; }
    int getIdNumber() const { return this->idNumber; }
    float getRadius() const { return this->boundary.getRadius(); }
    const sf::Vector2f& getVelocity() const { return this->velocity; }

    // setters
    void setBoundPos(const float x, const float y) { this->boundary.setPosition(x, y); }
    void setSpeed(float speed);
    void setIdNumber(int id) { this->idNumber = id; }
    void setRadius(const float radius);
    void setVelocity(const sf::Vector2f& velocity);
};
