#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"

Boid::Boid() : sf::CircleShape(BOID_DEFAULT_RADIUS, 3) {
    setFillColor(BOID_DEFAULT_COLOR);
}

void Boid::update(sf::Time deltaTime) {

    this->setRotation(vec2::angleDegrees(velocity)); // sets the front of the boid where it's going 
    this->move(velocity * deltaTime.asSeconds());
}

void Boid::setVelocity(const sf::Vector2f& velocity) {
    this->velocity = velocity;
}