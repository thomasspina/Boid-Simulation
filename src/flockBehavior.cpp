#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"

void FlockingBehavior::applySeparationLogic(Boid* currBoid, Boid* nborBoid, float& repulsionSumX, float& repulsionSumY) {
    float distance = vec2::distanceBetweenPoints(currBoid->getPosition(), nborBoid->getPosition()) * 0.01f; // TODO: 0.01f is a magic number
    repulsionSumX += (currBoid->getPosition().x - nborBoid->getPosition().x) / distance;
    repulsionSumY += (currBoid->getPosition().y - nborBoid->getPosition().y) / distance;
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
    
    float new_X = currBoid->getVelocity().x;
    float new_Y = currBoid->getVelocity().y;

    float repulsionXSum = 0.f;
    float repulsionYSum = 0.f;

    float avgVelocityX = 0.f;
    float avgVelocityY = 0.f;

    float avgPosX = 0.f;
    float avgPosY = 0.f;


    for (size_t i = 0; i < boids.size(); i++) {
        Boid* nborBoid = boids[i];

        if (boids[i]->getIdNumber() != currBoid->getIdNumber()) {

            if (currBoid->isWithinRadius(nborBoid->getPosition(), this->separationRadius)) {
                nborCount++;
                if (separationEnabled)
                    applySeparationLogic(currBoid, nborBoid, repulsionXSum, repulsionYSum);

            } else if (currBoid->isWithinRadius(nborBoid->getPosition(), currBoid->getNeighbourhoodRadius())) {
                nborCount++;
                if (alignmentEnabled)
                    applyAlignmentLogic(nborBoid, avgVelocityX, avgVelocityY);

                if (cohesionEnabled)
                    applyCohesionLogic(nborBoid, avgPosX, avgPosY);
            }
        }
    }

    if (nborCount == 0) {
        return;
    }

    if (alignmentEnabled) {
        new_X += (avgVelocityX / nborCount - currBoid->getVelocity().x) * this->matchingFactor;
        new_Y += (avgVelocityY / nborCount - currBoid->getVelocity().y) * this->matchingFactor;
    }

    if (cohesionEnabled) {
        new_X += (avgPosX / nborCount - currBoid->getPosition().x) * this->centeringFactor;
        new_Y += (avgPosY / nborCount - currBoid->getPosition().y) * this->centeringFactor;
    }

    if (separationEnabled) {
        new_X += currBoid->getVelocity().x + repulsionXSum * this->separationAvoidFactor;
        new_Y += currBoid->getVelocity().y + repulsionYSum * this->separationAvoidFactor;
    }

    // apply behavior to new vector
    currBoid->setVelocity(sf::Vector2(new_X, new_Y));
}

