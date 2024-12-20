#include "constants.hpp"
#include "flockingBehavior.hpp"
#include "utils.hpp"

// TODO separate in different respective methods
void flockingBehavior::applyFlockingLogic(Boid* currBoid, std::vector<Boid*>* boids) {
    int nborCount = 0;
    float velocityXSum = 0.f;
    float velocityYSum = 0.f;

    int repulseCount = 0;
    float repulsionXSum = 0.f;
    float repulsionYSum = 0.f;

    for (size_t i=currBoid->getIdNumber(); i < boids->size(); i++) {
        // neighbor currBoid
        Boid* nborBoid = (*boids)[i];

            // Set velocity of crossed boids to the average of neighboring boids (Alignment)
            if (currBoid->isWithinBoundary(nborBoid->getPosition(), BOID_DEFAULT_BOUNDARY_RADIUS)) {
                nborCount += 1;
                velocityXSum += nborBoid->getVelocity().x;
                velocityYSum += nborBoid->getVelocity().y;

                // std::cout << currBoid->getIdNumber() << " crossed " << nborBoid->getIdNumber() << "\n"; // TODO delete

                // Calculate repulsion vector for neighboring boids too close (Separation)
                if (currBoid->isWithinBoundary(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {
                    repulseCount += 1;
                    sf::Vector2f positionDiff = currBoid->getPosition() - nborBoid->getPosition();
                    float distanceBetween = std::max(1.0f, vec2::distanceBetweenPoints(currBoid->getVelocity(), nborBoid->getVelocity()));
                    
                    repulsionXSum += positionDiff.x / distanceBetween;
                    repulsionYSum += positionDiff.y / distanceBetween;
                }    
            }
    }

    if (nborCount != 0) {
        float averageRepulsionX = repulsionXSum / repulseCount;
        float averageRepulsionY = repulsionYSum / repulseCount;
        // float repulseNormalizer = vec2::distanceFormula(averageRepulsionX, 0, averageRepulsionY, 0); TODO Remove after done testing unit vector

        if (repulseCount != 0) {
            currBoid->setVelocity(sf::Vector2(velocityXSum / nborCount + averageRepulsionX,  velocityYSum / nborCount + averageRepulsionY));
        } else {
            currBoid->setVelocity(sf::Vector2(velocityXSum / nborCount,  velocityYSum / nborCount));
        }
    }
}
