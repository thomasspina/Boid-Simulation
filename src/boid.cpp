#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"

Boid::Boid() : sf::ConvexShape(3) {
    setPoint(0, sf::Vector2f(BOID_DEFAULT_RADIUS, 0.f));
    setPoint(1, sf::Vector2f(BOID_DEFAULT_RADIUS / 2, BOID_DEFAULT_RADIUS * 2));
    setPoint(2, sf::Vector2f(BOID_DEFAULT_RADIUS * 1.5f, BOID_DEFAULT_RADIUS * 2));

    setFillColor(BOID_DEFAULT_COLOR);

    // TODO: create centroid calculation in util
    float centroidX = (BOID_DEFAULT_RADIUS + BOID_DEFAULT_RADIUS / 2 + BOID_DEFAULT_RADIUS * 1.5f) / 3;
    float centroidY = (0.f + BOID_DEFAULT_RADIUS * 2 + BOID_DEFAULT_RADIUS * 2) / 3;

    // centers origin point to middle of boid instead of (0,0)
    this->setOrigin(centroidX, centroidY);
    this->setSpeed(BOID_DEFAULT_SPEED);

    initiateBoundary();
}

void Boid::initiateBoundary() {
    this->boundary = sf::CircleShape(BOID_DEFAULT_BOUNDARY_RADIUS);
    this->boundary.setFillColor(BOID_DEFAULT_BOUNDARY_COLOR);
    this->boundary.setOutlineColor(BOID_DEFAULT_BOUNDARY_OUTLINE_COLOR);
    this->boundary.setOutlineThickness(BOID_DEFAULT_BOUNDARY_OUTLINE_THICKNESS);
    this->boundary.setOrigin(BOID_DEFAULT_BOUNDARY_RADIUS, BOID_DEFAULT_BOUNDARY_RADIUS);
}

void Boid::update(const sf::Time& deltaTime) {
    sf::Vector2<float> newPos = velocity * deltaTime.asSeconds();
    this->move(newPos);
    this->boundary.move(newPos);
}

// check whether a neighbor boid is within the current boid's boundary
bool Boid::isWithinBoundary(const sf::Vector2f& neighborVector, float radius) const {
    return vec2::distanceBetweenPoints(this->getPosition(), neighborVector) <= radius;
}

void Boid::setRadius(const float radius) {
    this->boundary.setRadius(radius);
    this->boundary.setOrigin(radius, radius);
}

void Boid::setSpeed(float speed) {
    this->speed = speed;
    this->velocity = vec2::vecFromDegree(this->getRotation()) * speed; // update velocity when speed update
}

void Boid::setVelocity(const sf::Vector2f& velocity) {
    this->velocity = velocity;
    this->setRotation(vec2::angleDegrees(this->velocity)); // sets the front of the boid where it's going   
}