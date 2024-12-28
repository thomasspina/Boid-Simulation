#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"

void FlockingBehavior::applySeparationLogic(Boid* currBoid, Boid* nborBoid, float& repulsionXSum, float& repulsionYSum) {
    float distance = vec2::distanceBetweenPoints(currBoid->getPosition(), nborBoid->getPosition()) * 0.01f; // TODO: 0.01f is a magic number
    repulsionXSum += (currBoid->getPosition().x - nborBoid->getPosition().x) / distance;
    repulsionYSum += (currBoid->getPosition().y - nborBoid->getPosition().y) / distance;
}

void FlockingBehavior::applyAlignmentLogic(Boid* nborBoid, float& avgVelocityX, float& avgVelocityY) {
        avgVelocityX += nborBoid->getVelocity().x;
        avgVelocityY += nborBoid->getVelocity().y;
}

void FlockingBehavior::applyCohesionLogic(Boid* nborBoid, float& avgPosX, float& avgPosY) {
        avgPosX += nborBoid->getPosition().x;
        avgPosY += nborBoid->getPosition().y;
}

void FlockingBehavior::applyFlockingLogic(Boid* currBoid, const std::vector<Boid*>& boids) {
    int nborCount = 0;

    const sf::Vector2f& currVel = currBoid->getVelocity();
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

        if (nborBoid->getIdNumber() != currBoidId) {

            if (currBoid->isWithinRadius(nborPos, this->separationRadius)) {
                nborCount++;
                if (separationEnabled) {
                    applySeparationLogic(currBoid, nborBoid, repulsionXSum, repulsionYSum);
                }
            } else if (currBoid->isWithinRadius(nborPos, neighbourRadius)) {
                nborCount++;
                if (alignmentEnabled) {
                    applyAlignmentLogic(nborBoid, avgVelocityX, avgVelocityY);
                }

                if (cohesionEnabled) {
                    applyCohesionLogic(nborBoid, avgPosX, avgPosY);
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

