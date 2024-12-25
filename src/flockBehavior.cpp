#include <iostream>

#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"

// TODO: separate in different respective methods
void flockingBehavior::applyFlockingLogic(Boid* currBoid, std::vector<Boid*>* boids) {
    int nborCount = 0;
    float avgVelocityX = 0.f;
    float avgVelocityY = 0.f;

    int repulseCount = 0;
    float repulsionXSum = 0.f;
    float repulsionYSum = 0.f;

    for (size_t i=currBoid->getIdNumber(); i < boids->size(); i++) {
        // neighbor currBoid
        Boid* nborBoid = (*boids)[i];

            // Set velocity of crossed boids to the average of neighboring boids (Alignment)
            if (currBoid->isWithinBoundary(nborBoid->getPosition(), currBoid->getRadius())) {
                nborCount += 1;
                avgVelocityX += nborBoid->getVelocity().x;
                avgVelocityY += nborBoid->getVelocity().y;

                // std::cout << currBoid->getIdNumber() << " crossed " << nborBoid->getIdNumber() << "\n"; // TODO delete

                // Calculate repulsion unit vector for neighboring boids within boundary (Separation)
                if (currBoid->isWithinBoundary(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {
                    repulsionXSum += currBoid->getPosition().x - nborBoid->getPosition().x;
                    repulsionYSum += currBoid->getPosition().y - nborBoid->getPosition().y;

                // sf::Vector2f vectorDifference = currBoid->getPosition() - nborBoid->getPosition();
                // float distanceDifference = vec2::distanceBetweenPoints(currBoid->getPosition(), nborBoid->getPosition());
                // if (distanceDifference > 0.0f) {
                //     sf::Vector2f repulseUV = vectorDifference / distanceDifference;
                //     repulsionXSum += repulseUV.x;
                //     repulsionYSum += repulseUV.y;
                }


                // float distanceBetween = std::max(1.0f, vec2::distanceBetweenPoints(currBoid->getVelocity(), nborBoid->getVelocity()));
               
                // std::cout << repulseUV.x << " " << repulseUV.y << "\n";


                // // Calculate repulsion vector for neighboring boids too close (Separation)
                // if (currBoid->isWithinBoundary(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {
                //     repulseCount += 1;
                //     sf::Vector2f positionDiff = currBoid->getPosition() - nborBoid->getPosition();
                //     float distanceBetween = std::max(1.0f, vec2::distanceBetweenPoints(currBoid->getVelocity(), nborBoid->getVelocity()));
                    
                //     repulsionXSum += positionDiff.x / distanceBetween;
                //     repulsionYSum += positionDiff.y / distanceBetween;
                // }    
            }
    }


    if (nborCount > 0) {
        avgVelocityX = avgVelocityX / nborCount;
        avgVelocityY = avgVelocityY / nborCount;

        // Apply separation behavior
        float new_X = currBoid->getVelocity().x + repulsionXSum * FLOCK_DEFAULT_AVOID_FACTOR;
        float new_Y = currBoid->getVelocity().y + repulsionYSum * FLOCK_DEFAULT_AVOID_FACTOR;

        // Apply alignment behavior
        new_X += (avgVelocityX - currBoid->getVelocity().x) * FLOCK_DEFAULT_MATCHING_FACTOR;
        new_Y += (avgVelocityY - currBoid->getVelocity().y) * FLOCK_DEFAULT_MATCHING_FACTOR;

        currBoid->setVelocity(sf::Vector2(new_X, new_Y));
    }


    // if (nborCount != 0) {
    //     float averageRepulsionX = repulsionXSum / repulseCount;
    //     float averageRepulsionY = repulsionYSum / repulseCount;
    //     // float repulseNormalizer = vec2::distanceFormula(averageRepulsionX, 0, averageRepulsionY, 0); TODO Remove after done testing unit vector

    //     if (repulseCount != 0) {
    //         currBoid->setVelocity(sf::Vector2(velocityXSum / nborCount + averageRepulsionX,  velocityYSum / nborCount + averageRepulsionY));
    //     } else {
    //         currBoid->setVelocity(sf::Vector2(velocityXSum / nborCount,  velocityYSum / nborCount));
    //     }
    // }
}
