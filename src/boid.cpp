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

float Boid::getRadius() const {
    return this->boundary.getRadius();
}

void Boid::setRadius(const float radius) {
    this->boundary.setRadius(radius);
}

const sf::CircleShape& Boid::getBoundary() const {
    return this->boundary;
}

void Boid::setBoundPos(const float x, const float y) {
    this->boundary.setPosition(x, y);
}

void Boid::setSpeed(float speed) {
    this->speed = speed;
}
    
float Boid::getSpeed() const {
    return this->speed;
}

void Boid::setIdNumber(int id) {
    this->idNumber = id;
}
    
int Boid::getIdNumber() const {
    return this->idNumber;
}

void Boid::update(const sf::Time& deltaTime) {
    speed = vec2::distanceFormula(velocity.x, 0, velocity.y, 0);

    if (speed > BOID_DEFAULT_MAX_SPEED) {
        velocity.x = (velocity.x/speed)*BOID_DEFAULT_MAX_SPEED;
        velocity.y = (velocity.y/speed)*BOID_DEFAULT_MAX_SPEED;
    }

    if (speed < BOID_DEFAULT_MIN_SPEED) {
         velocity.x = (velocity.x/speed)*BOID_DEFAULT_MIN_SPEED;
        velocity.y = (velocity.y/speed)*BOID_DEFAULT_MIN_SPEED;
    }

    auto newPos = velocity * deltaTime.asSeconds();
    this->move(newPos);
    this->boundary.move(newPos);
}

void Boid::setVelocity(const sf::Vector2f& velocity) {
    this->setRotation(vec2::angleDegrees(velocity)); // sets the front of the boid where it's going 
    this->velocity = velocity;
}

const sf::Vector2f& Boid::getVelocity() const {
    return this->velocity;
}

// check whether a neighbor boid is within the current boid's boundary
bool Boid::isWithinBoundary(const sf::Vector2f& neighborVector, float radius) const {
    return vec2::distanceBetweenPoints(this->getPosition(), neighborVector) <= radius;
}
