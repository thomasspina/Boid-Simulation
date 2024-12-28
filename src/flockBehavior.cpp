#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"

void FlockingBehavior::applySeparationLogic(const sf::Vector2f& currBoidPos, const sf::Vector2f& nborBoidPos, float& repulsionXSum, float& repulsionYSum) {
    float distance = vec2::distanceBetweenPoints(currBoidPos, nborBoidPos) * 0.01f; // TODO: 0.01f is a magic number
    repulsionXSum += (currBoidPos.x - nborBoidPos.x) / distance;
    repulsionYSum += (currBoidPos.y - nborBoidPos.y) / distance;
}

void FlockingBehavior::applyAlignmentLogic(const sf::Vector2f& nborVel, float& avgVelocityX, float& avgVelocityY) {
        avgVelocityX += nborVel.x;
        avgVelocityY += nborVel.y;
}

void FlockingBehavior::applyCohesionLogic(const sf::Vector2f& nborBoidPos, float& avgPosX, float& avgPosY) {
        avgPosX += nborBoidPos.x;
        avgPosY += nborBoidPos.y;
}

void FlockingBehavior::applyFlockingLogic(Boid* currBoid, const std::vector<Boid*>& boids) {
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
                if (separationEnabled) {
                    applySeparationLogic(currPos, nborPos, repulsionXSum, repulsionYSum);
                }
            } else if (currBoid->isWithinRadius(nborPos, neighbourRadius)) {
                nborCount++;
                if (alignmentEnabled) {
                    applyAlignmentLogic(nborVel, avgVelocityX, avgVelocityY);
                }

                if (cohesionEnabled) {
                    applyCohesionLogic(nborPos, avgPosX, avgPosY);
                }
            }
        }
    }

    if (nborCount == 0) {
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
}

