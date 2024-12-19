#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include <iostream> // TODO remove

Boid::Boid() : sf::CircleShape(BOID_DEFAULT_RADIUS, 3) {
    setFillColor(BOID_DEFAULT_COLOR);
}

void Boid::update(const sf::Time& deltaTime) {
    this->move(velocity * deltaTime.asSeconds());
}

void Boid::setVelocity(const sf::Vector2f& velocity) {
    this->setRotation(vec2::angleDegrees(velocity)); // sets the front of the boid where it's going 
    this->velocity = velocity;
}
