#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include <iostream> // TODO remove

Boid::Boid() : sf::CircleShape(BOID_DEFAULT_RADIUS, 3) {
    setFillColor(BOID_DEFAULT_COLOR);

    // centers origin point to middle of boid instead of (0,0)
    this->setOrigin(BOID_DEFAULT_RADIUS, BOID_DEFAULT_RADIUS);

    initiateBoundary();
}

void Boid::initiateBoundary() {
    this->boundary = sf::CircleShape(BOID_DEFAULT_BOUNDARY_RADIUS);
    this->boundary.setFillColor(BOID_DEFAULT_BOUNDARY_COLOR);
    this->boundary.setOutlineColor(BOID_DEFAULT_BOUNDARY_OUTLINE_COLOR);
    this->boundary.setOutlineThickness(BOID_DEFAULT_BOUNDARY_OUTLINE_THICKNESS);
}

void Boid::update(const sf::Time& deltaTime) {
    auto newPos = velocity * deltaTime.asSeconds();
    this->move(newPos);
    this->boundary.move(newPos);
}

void Boid::setVelocity(const sf::Vector2f& velocity) {
    this->setRotation(vec2::angleDegrees(velocity)); // sets the front of the boid where it's going 
    this->velocity = velocity;
}

// check whether a neighbor boid is within the current boid's boundary
bool Boid::isWithinBoundary(sf::Vector2f& neighborVector) {
    return vec2::distanceBetweenPoints(this->getPosition(), neighborVector) <= BOID_DEFAULT_BOUNDARY_RADIUS;
}
