#pragma once

#include <random>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include <SFML/System/Clock.hpp>

#include "constants.hpp"

class Boid : public sf::ConvexShape {
private:
    sf::Vector2f velocity = {0.f, 0.f};
    sf::CircleShape neighbourhoodBoundary;
    int idNumber;
    float speed = 0.f;
    float wanderAngle = 0.f;
    float maxSpeed = BOID_DEFAULT_MAX_SPEED;
public:
    Boid();

    void initNeighbourhoodBoundary();
    void update(const sf::Time& deltaTime);
    bool isWithinRadius(const sf::Vector2f& neighborVector, const float radius) const;

    // getters
    const sf::CircleShape& getNeighbourhoodBoundary() const { return this->neighbourhoodBoundary; }
    float getSpeed() const { return this->speed; }
    int getIdNumber() const { return this->idNumber; }
    float getNeighbourhoodRadius() const { return this->neighbourhoodBoundary.getRadius(); }
    const sf::Vector2f& getVelocity() const { return this->velocity; }
    float getWanderAngle() const { return this->wanderAngle; }

    // setters
    void setBoundPos(const float x, const float y) { this->neighbourhoodBoundary.setPosition(x, y); }
    void setSpeed(float speed);
    void setIdNumber(int id) { this->idNumber = id; }
    void setNeighboorhoodRadius(const float radius);
    void setVelocity(const sf::Vector2f& velocity);
    void setMaxSpeed(const float speed) { this->maxSpeed = speed; }
    void setWanderAngle(const float angle) { this->wanderAngle = angle; }
};
