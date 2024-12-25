#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"

void FlockingBehavior::applyFlockingLogic(Boid* currBoid, std::vector<Boid*>* boids) {
    int nborCount = 0;

    float avgVelocityX = 0.f;
    float avgVelocityY = 0.f;

    float avgPosX = 0.f;
    float avgPosY = 0.f;

    int repulseCount = 0;
    float repulsionXSum = 0.f;
    float repulsionYSum = 0.f;

    for (size_t i=currBoid->getIdNumber(); i < boids->size(); i++) {
        // neighbor currBoid
        Boid* nborBoid = (*boids)[i];

            // Set velocity of crossed boids to the average of neighboring boids (Alignment)
            if (currBoid->isWithinRadius(nborBoid->getPosition(), currBoid->getNeighbourhoodRadius())) {

                // Calculate repulsion unit vector for neighboring boids within boundary (Separation)
                if (currBoid->isWithinRadius(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {
                    repulsionXSum += currBoid->getPosition().x - nborBoid->getPosition().x;
                    repulsionYSum += currBoid->getPosition().y - nborBoid->getPosition().y;
                } else {
                    nborCount += 1;
                    avgVelocityX += nborBoid->getVelocity().x;
                    avgVelocityY += nborBoid->getVelocity().y;

                    avgPosX += nborBoid->getPosition().x;
                    avgPosY += nborBoid->getPosition().y;
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
    new_X += currBoid->getVelocity().x + repulsionXSum * FLOCK_DEFAULT_AVOID_FACTOR;
    new_Y += currBoid->getVelocity().y + repulsionYSum * FLOCK_DEFAULT_AVOID_FACTOR;

    sf::Vector2f newVelocity = sf::Vector2(new_X, new_Y);

    currBoid->setVelocity(newVelocity);
}
