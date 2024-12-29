#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"

void FlockingBehavior::applySeparationLogic(const sf::Vector2f& currBoidPos, const sf::Vector2f& nborBoidPos, float& repulsionXSum, float& repulsionYSum) {
    if (!separationEnabled) return;

    float distance = vec2::distanceBetweenPoints(currBoidPos, nborBoidPos) * BOID_DISTANCE_CALCULATION_SCALER;
    repulsionXSum += (currBoidPos.x - nborBoidPos.x) / distance;
    repulsionYSum += (currBoidPos.y - nborBoidPos.y) / distance;
}

void FlockingBehavior::applyAlignmentLogic(const sf::Vector2f& nborVel, float& avgVelocityX, float& avgVelocityY) {
    if (!alignmentEnabled) return;

    avgVelocityX += nborVel.x;
    avgVelocityY += nborVel.y;
}

void FlockingBehavior::applyCohesionLogic(const sf::Vector2f& nborBoidPos, float& avgPosX, float& avgPosY) {
    if (!cohesionEnabled) return;

    avgPosX += nborBoidPos.x;
    avgPosY += nborBoidPos.y;
}

void FlockingBehavior::applyWanderLogic(Boid* boid, const sf::Vector2f& vel, const sf::Time& dT) {
    if (!isWanderEnabled) return;

    float wanderAngle = boid->getWanderAngle();

    const sf::Vector2f normalized = vec2::normalize(vel);

    // project a displacement circle in the boid direction
    sf::Vector2f circleCenter(normalized.x * BOID_WANDER_CIRCLE_DISTANCE, normalized.y * BOID_WANDER_CIRCLE_DISTANCE);

    // set a random point on the displacement unit circle, constant dictates how wide the angle change is
    wanderAngle += (rand() / (float)RAND_MAX - 0.5f) * 2.0f * BOID_WANDER_ANGLE_CHANGE;
    
    // Calculate the displacement force on the circle that is scaled to the desired radius
    sf::Vector2f displacement(std::cos(wanderAngle) * BOID_WANDER_CIRCLE_RADIUS, std::sin(wanderAngle) * BOID_WANDER_CIRCLE_RADIUS);
    
    // Combine circle center and displacement to get final wander force
    sf::Vector2f wanderForce = circleCenter + displacement;

    boid->setVelocity(vel + wanderForce * this->wanderFactor * dT.asSeconds());
}

void FlockingBehavior::applyFlockingLogic(Boid* currBoid, const std::vector<Boid*>& boids, const sf::Time& dT) {
    int nborCount = 0;

    const sf::Vector2f& currVel = currBoid->getVelocity();
    const sf::Vector2f& currPos = currBoid->getPosition();

    float new_X = currVel.x;
    float new_Y = currVel.y;

    float repulsionXSum = 0.f;
    float repulsionYSum = 0.f;

    float avgVelocityX = 0.f;
    float avgVelocityY = 0.f;

    float avgPosX = 0.f;
    float avgPosY = 0.f;

    int currBoidId = currBoid->getIdNumber();
    float neighbourRadius = currBoid->getNeighbourhoodRadius();
    for (size_t i = 0; i < boids.size(); i++) {
        Boid* nborBoid = boids[i];
        const sf::Vector2f& nborPos = nborBoid->getPosition();
        const sf::Vector2f& nborVel = nborBoid->getVelocity();

        if (nborBoid->getIdNumber() != currBoidId) {

            if (currBoid->isWithinRadius(nborPos, this->separationRadius)) {
                nborCount++;
                applySeparationLogic(currPos, nborPos, repulsionXSum, repulsionYSum);
            } else if (currBoid->isWithinRadius(nborPos, neighbourRadius)) {
                nborCount++;
                applyAlignmentLogic(nborVel, avgVelocityX, avgVelocityY);
                applyCohesionLogic(nborPos, avgPosX, avgPosY);
            }
        }
    }

    if (nborCount == 0) {
        applyWanderLogic(currBoid, currBoid->getVelocity(), dT);
        return;
    }

    if (alignmentEnabled) {
        new_X += (avgVelocityX / nborCount - currVel.x) * this->matchingFactor;
        new_Y += (avgVelocityY / nborCount - currVel.y) * this->matchingFactor;
    }

    if (cohesionEnabled) {
        new_X += (avgPosX / nborCount - currBoid->getPosition().x) * this->centeringFactor;
        new_Y += (avgPosY / nborCount - currBoid->getPosition().y) * this->centeringFactor;
    }

    if (separationEnabled) {
        new_X += currVel.x + repulsionXSum * this->separationAvoidFactor;
        new_Y += currVel.y + repulsionYSum * this->separationAvoidFactor;
    }

    // apply behavior to new vector
    currBoid->setVelocity(sf::Vector2(new_X, new_Y));

    applyWanderLogic(currBoid, currBoid->getVelocity(), dT);
}

void FlockingBehavior::applyMouseAvoidanceLogic(Boid* currBoid, sf::Vector2f mousePos, float& currX, float& currY) {
    sf::Vector2f boidPosition = currBoid->getPosition();

    float distance = vec2::distanceBetweenPoints(boidPosition, mousePos) * BOID_DISTANCE_CALCULATION_SCALER;
    float repulsionX = (boidPosition.x - mousePos.x) / distance;
    float repulsionY = (boidPosition.y - mousePos.y) / distance;

    currX += repulsionX * BOID_DEFAULT_MOUSE_AVOIDANCE_FACTOR;
    currY += repulsionY * BOID_DEFAULT_MOUSE_AVOIDANCE_FACTOR;
}
 
void FlockingBehavior::applyMouseAvoidance(Boid* currBoid, sf::Vector2f mousePos) {

    if (mouseAvoidanceEnable) {
        
        if (currBoid->isWithinRadius(mousePos, BOID_DEFAULT_MOUSE_AVOIDANCE_RADIUS)) {

            float new_X = 0.f;
            float new_Y = 0.f;

            new_X = currBoid->getVelocity().x;
            new_Y = currBoid->getVelocity().y;

            applyMouseAvoidanceLogic(currBoid, mousePos, new_X, new_Y);

            currBoid->setVelocity(sf::Vector2(new_X, new_Y));
        }
    }
}
