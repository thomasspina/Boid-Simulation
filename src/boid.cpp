#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include <random>

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

    initNeighbourhoodBoundary();
}

void Boid::initNeighbourhoodBoundary() {
    this->neighbourhoodBoundary = sf::CircleShape(BOID_DEFAULT_NEIGHBOURHOOD_RADIUS);
    this->neighbourhoodBoundary.setFillColor(BOID_DEFAULT_NEIGHBOURHOOD_COLOR);
    this->neighbourhoodBoundary.setOutlineColor(BOID_DEFAULT_NEIGHBOURHOOD_OUTLINE_COLOR);
    this->neighbourhoodBoundary.setOutlineThickness(BOID_DEFAULT_NEIGHBOURHOOD_OUTLINE_THICKNESS);
    this->neighbourhoodBoundary.setOrigin(BOID_DEFAULT_NEIGHBOURHOOD_RADIUS, BOID_DEFAULT_NEIGHBOURHOOD_RADIUS);
}

void Boid::update(const sf::Time& deltaTime) {
    sf::Vector2f normalized = vec2::normalize(velocity);

    // Project a displacement circle in the boid direction
    sf::Vector2f circleCenter(normalized.x * BOID_WANDER_CIRCLE_DISTANCE, normalized.y * BOID_WANDER_CIRCLE_DISTANCE);

    // Set a random point on the displacement unit circle, constant dictates how wide the angle change is
    wanderAngle += (rand() / (float)RAND_MAX - 0.5f) * 2.0f * BOID_WANDER_ANGLE_CHANGE;
    
    // Calculate the displacement force on the circle that is scaled to the desired radius
    sf::Vector2f displacement(std::cos(wanderAngle) * BOID_WANDER_CIRCLE_RADIUS, std::sin(wanderAngle) * BOID_WANDER_CIRCLE_RADIUS);
    
    // Combine circle center and displacement to get final wander force
    sf::Vector2f wanderForce = circleCenter + displacement;

    // Apply wander vector
    setVelocity(velocity += wanderForce * BOID_WANDER_FORCE_FACTOR * deltaTime.asSeconds());

    sf::Vector2<float> newPos = velocity * deltaTime.asSeconds();
    this->move(newPos);
    this->neighbourhoodBoundary.move(newPos);
}

// check whether a neighbor boid is within the current boid's boundary
bool Boid::isWithinRadius(const sf::Vector2f& neighborVector, float radius) const {
    return vec2::distanceBetweenPoints(this->getPosition(), neighborVector) <= radius;
}

void Boid::setNeighboorhoodRadius(const float radius) {
    this->neighbourhoodBoundary.setRadius(radius);
    this->neighbourhoodBoundary.setOrigin(radius, radius);
}

void Boid::setSpeed(float speed) {
    this->speed = speed;
    this->velocity = vec2::vecFromDegree(this->getRotation()) * speed; // update velocity when speed update
}

void Boid::setVelocity(const sf::Vector2f& velocity) {
    this->velocity = velocity;
    this->setRotation(vec2::angleDegrees(this->velocity)); // sets the front of the boid where it's going   

    if (vec2::getMagnitude(velocity) > BOID_DEFAULT_MAX_SPEED) {
        this->velocity = vec2::normalize(velocity) * BOID_DEFAULT_MAX_SPEED;
    } else if (vec2::getMagnitude(velocity) < BOID_DEFAULT_MIN_SPEED) {
        this->velocity = vec2::normalize(velocity) * BOID_DEFAULT_MIN_SPEED;
    }
}
