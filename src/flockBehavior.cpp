#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"
#include <algorithm>
#include <utility> 

void FlockingBehavior::applyFlockingLogic(Boid* currBoid, std::vector<Boid*>* boids) {
    int nborCount = 0;

    float avgVelocityX = 0.f;
    float avgVelocityY = 0.f;

    float avgPosX = 0.f;
    float avgPosY = 0.f;

    // float repulsionXSum = 0.f;
    // float repulsionYSum = 0.f;
    std::pair<float, float> repulsionSum = applySeparationLogic(currBoid, boids);

    for (size_t i=0; i < boids->size(); i++) {
        // neighbor currBoid
        Boid* nborBoid = (*boids)[i];

        if (nborBoid->getIdNumber() != currBoid->getIdNumber()) {

            // Set velocity of crossed boids to the average of neighboring boids (Alignment)
            if (currBoid->isWithinRadius(nborBoid->getPosition(), currBoid->getNeighbourhoodRadius())) {
                nborCount += 1;
                avgVelocityX += nborBoid->getVelocity().x;
                avgVelocityY += nborBoid->getVelocity().y;

                avgPosX += nborBoid->getPosition().x;
                avgPosY += nborBoid->getPosition().y;
                // // Calculate repulsion unit vector for neighboring boids within boundary (Separation)
                // if (currBoid->isWithinRadius(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {
                //     float distance = vec2::distanceBetweenPoints(currBoid->getPosition(), nborBoid->getPosition()) * 0.01f;
                //     // distance = std::min(distance, 1000.0f);
                //     // std::cout << distance << "\n";
                //     // std::cout << nborBoid->getPosition().x << " " << nborBoid->getPosition().x << "\n";
                //     repulsionXSum += (currBoid->getPosition().x - nborBoid->getPosition().x) / distance;
                //     repulsionYSum += (currBoid->getPosition().y - nborBoid->getPosition().y) / distance;
                // } else {
                //     nborCount += 1;
                //     avgVelocityX += nborBoid->getVelocity().x;
                //     avgVelocityY += nborBoid->getVelocity().y;

                //     avgPosX += nborBoid->getPosition().x;
                //     avgPosY += nborBoid->getPosition().y;
                // }
            }
        }
    }


    float new_X = currBoid->getVelocity().x;
    float new_Y = currBoid->getVelocity().y;

    if (nborCount > 0) {
        avgVelocityX /= nborCount;
        avgVelocityY /= nborCount;

        avgPosX /= nborCount;
        avgPosY /= nborCount;

        // Apply alignment behavior
        new_X += (avgVelocityX - currBoid->getVelocity().x) * FLOCK_DEFAULT_MATCHING_FACTOR;
        new_Y += (avgVelocityY - currBoid->getVelocity().y) * FLOCK_DEFAULT_MATCHING_FACTOR;

        // Apply cohesion behavior
        new_X += (avgPosX - currBoid->getPosition().x) * FLOCK_DEFAULT_CENTERING_FACTOR;
        new_Y += (avgPosY - currBoid->getPosition().y) * FLOCK_DEFAULT_CENTERING_FACTOR;
    }

    // Apply separation behavior
    new_X += currBoid->getVelocity().x + repulsionSum.first * FLOCK_DEFAULT_AVOID_FACTOR;
    new_Y += currBoid->getVelocity().y + repulsionSum.second * FLOCK_DEFAULT_AVOID_FACTOR;

    sf::Vector2f newVelocity = sf::Vector2(new_X, new_Y);

    currBoid->setVelocity(newVelocity);
}

std::pair<float, float> FlockingBehavior::applySeparationLogic(Boid* currBoid, std::vector<Boid*>* boids) {
    float repulsionXSum = 0.f;
    float repulsionYSum = 0.f;

    for (size_t i=0; i < boids->size(); i++) {
        Boid* nborBoid = (*boids)[i];

        if (currBoid->isWithinRadius(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {
            float distance = vec2::distanceBetweenPoints(currBoid->getPosition(), nborBoid->getPosition()) * 0.01f;
            repulsionXSum += (currBoid->getPosition().x - nborBoid->getPosition().x) / distance;
            repulsionYSum += (currBoid->getPosition().y - nborBoid->getPosition().y) / distance;
        }
    }

    return std::make_pair(repulsionXSum, repulsionYSum);
}
