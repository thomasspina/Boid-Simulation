#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"

int FlockingBehavior::countNeighbours(Boid* currBoid, std::vector<Boid*>* boids) {
    int nborCount = 0;

    for (size_t i=0; i < boids->size(); i++) {
        Boid* nborBoid = (*boids)[i];

        if (nborBoid->getIdNumber() != currBoid->getIdNumber()) {
            if (!currBoid->isWithinRadius(nborBoid->getPosition(), this->separationRadius)) {

                if (currBoid->isWithinRadius(nborBoid->getPosition(), currBoid->getNeighbourhoodRadius())) {
                    nborCount++;
                }

            } 
        }
    }

    return nborCount;
}

void FlockingBehavior::applyFlockingLogic(Boid* currBoid, std::vector<Boid*>* boids) {
    int nborCount = countNeighbours(currBoid, boids);
    
    float new_X = currBoid->getVelocity().x;
    float new_Y = currBoid->getVelocity().y;

    if (nborCount > 0) {
        // Apply alignment behavior
        if (alignmentEnabled) {
            std::pair<float, float> velocityAvg = applyAlignmentLogic(currBoid, boids, nborCount);

            new_X += (velocityAvg.first - currBoid->getVelocity().x) * this->matchingFactor;
            new_Y += (velocityAvg.second - currBoid->getVelocity().y) * this->matchingFactor;
        }

        // Apply cohesion behavior
        if (cohesionEnabled) {
            std::pair<float, float> positionAvg = applyCohesionLogic(currBoid, boids, nborCount);

            new_X += (positionAvg.first - currBoid->getPosition().x) * this->centeringFactor;
            new_Y += (positionAvg.second - currBoid->getPosition().y) * this->centeringFactor;;
        }
    }

    // Apply separation behavior
    if (separationEnabled) {
        std::pair<float, float> repulsionSum = applySeparationLogic(currBoid, boids);

        new_X += currBoid->getVelocity().x + repulsionSum.first * this->separationAvoidFactor;
        new_Y += currBoid->getVelocity().y + repulsionSum.second * this->separationAvoidFactor;
    }
    
    // Apply behavior to new vector
    sf::Vector2f newVelocity = sf::Vector2(new_X, new_Y);

    currBoid->setVelocity(newVelocity);
}

std::pair<float, float> FlockingBehavior::applySeparationLogic(Boid* currBoid, std::vector<Boid*>* boids) {
    float repulsionXSum = 0.f;
    float repulsionYSum = 0.f;

    for (size_t i=0; i < boids->size(); i++) {
        Boid* nborBoid = (*boids)[i];

        if (nborBoid->getIdNumber() != currBoid->getIdNumber()) {

            if (currBoid->isWithinRadius(nborBoid->getPosition(), this->separationRadius)) {
                float distance = vec2::distanceBetweenPoints(currBoid->getPosition(), nborBoid->getPosition()) * 0.01f;
                repulsionXSum += (currBoid->getPosition().x - nborBoid->getPosition().x) / distance;
                repulsionYSum += (currBoid->getPosition().y - nborBoid->getPosition().y) / distance;
            }
        }
    }

    return {repulsionXSum, repulsionYSum};
}

std::pair<float, float> FlockingBehavior::applyAlignmentLogic(Boid* currBoid, std::vector<Boid*>* boids, int nborCount) {
    float avgVelocityX = 0.f;
    float avgVelocityY = 0.f;

    for (size_t i=0; i < boids->size(); i++) {
        Boid* nborBoid = (*boids)[i];

        if (nborBoid->getIdNumber() != currBoid->getIdNumber()) {

            if (!currBoid->isWithinRadius(nborBoid->getPosition(), this->separationRadius)) {

                if (currBoid->isWithinRadius(nborBoid->getPosition(), currBoid->getNeighbourhoodRadius())) {
                    avgVelocityX += nborBoid->getVelocity().x;
                    avgVelocityY += nborBoid->getVelocity().y;
                }
            }
        }
    }

    return {avgVelocityX / nborCount, avgVelocityY / nborCount};
}

std::pair<float, float> FlockingBehavior::applyCohesionLogic(Boid* currBoid, std::vector<Boid*>* boids, int nborCount) {
    float avgPosX = 0.f;
    float avgPosY = 0.f;

    for (size_t i=0; i < boids->size(); i++) {
        Boid* nborBoid = (*boids)[i];

        if (nborBoid->getIdNumber() != currBoid->getIdNumber()) {

            if (!currBoid->isWithinRadius(nborBoid->getPosition(), this->separationRadius)) {

                if (currBoid->isWithinRadius(nborBoid->getPosition(), currBoid->getNeighbourhoodRadius())) {
                    avgPosX += nborBoid->getPosition().x;
                    avgPosY += nborBoid->getPosition().y;
                }
            }
        }
    }
    return {avgPosX / nborCount, avgPosY / nborCount};
}

