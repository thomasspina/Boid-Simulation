#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"

void FlockingBehavior::applyFlockingLogic(Boid* currBoid, std::vector<Boid*>* boids) {
    int nborCount = 0;

    std::pair<float, float> velocityAvg = applyAlignmentLogic(currBoid, boids, nborCount);
    std::pair<float, float> positionAvg = applyCohesionLogic(currBoid, boids, nborCount);
    std::pair<float, float> repulsionSum = applySeparationLogic(currBoid, boids);

    float new_X = currBoid->getVelocity().x;
    float new_Y = currBoid->getVelocity().y;

    if (nborCount > 0) {
        // Apply alignment behavior
        new_X += (velocityAvg.first - currBoid->getVelocity().x) * FLOCK_DEFAULT_MATCHING_FACTOR;
        new_Y += (velocityAvg.second - currBoid->getVelocity().y) * FLOCK_DEFAULT_MATCHING_FACTOR;

        // Apply cohesion behavior
        new_X += (positionAvg.first - currBoid->getPosition().x) * FLOCK_DEFAULT_CENTERING_FACTOR;
        new_Y += (positionAvg.second - currBoid->getPosition().y) * FLOCK_DEFAULT_CENTERING_FACTOR;
    }

    // Apply separation behavior
    new_X += currBoid->getVelocity().x + repulsionSum.first * FLOCK_DEFAULT_AVOID_FACTOR;
    new_Y += currBoid->getVelocity().y + repulsionSum.second * FLOCK_DEFAULT_AVOID_FACTOR;

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

            if (currBoid->isWithinRadius(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {
                float distance = vec2::distanceBetweenPoints(currBoid->getPosition(), nborBoid->getPosition()) * 0.01f;
                repulsionXSum += (currBoid->getPosition().x - nborBoid->getPosition().x) / distance;
                repulsionYSum += (currBoid->getPosition().y - nborBoid->getPosition().y) / distance;
            }
        }
    }

    return {repulsionXSum, repulsionYSum};
}

std::pair<float, float> FlockingBehavior::applyAlignmentLogic(Boid* currBoid, std::vector<Boid*>* boids, int& nborCount) {
    float avgVelocityX = 0.f;
    float avgVelocityY = 0.f;

    for (size_t i=0; i < boids->size(); i++) {
        Boid* nborBoid = (*boids)[i];

        if (nborBoid->getIdNumber() != currBoid->getIdNumber()) {

            if (!currBoid->isWithinRadius(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {

                if (currBoid->isWithinRadius(nborBoid->getPosition(), currBoid->getNeighbourhoodRadius())) {
                    // Apply neighbor count
                    nborCount += 1;
                    avgVelocityX += nborBoid->getVelocity().x;
                    avgVelocityY += nborBoid->getVelocity().y;
                }
            }
        }
    }

    return {avgVelocityX / nborCount, avgVelocityY / nborCount};
}

std::pair<float, float> FlockingBehavior::applyCohesionLogic(Boid* currBoid, std::vector<Boid*>* boids, int& nborCount) {
    float avgPosX = 0.f;
    float avgPosY = 0.f;

    for (size_t i=0; i < boids->size(); i++) {
        Boid* nborBoid = (*boids)[i];

        if (nborBoid->getIdNumber() != currBoid->getIdNumber()) {

            if (!currBoid->isWithinRadius(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {

                if (currBoid->isWithinRadius(nborBoid->getPosition(), currBoid->getNeighbourhoodRadius())) {
                    avgPosX += nborBoid->getPosition().x;
                    avgPosY += nborBoid->getPosition().y;
                }
            }
        }
    }
    return {avgPosX / nborCount, avgPosY / nborCount};
}

