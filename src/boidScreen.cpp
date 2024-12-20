#include "boidScreen.hpp"

#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>

BoidScreen::BoidScreen(sf::RenderWindow* windowPointer) : windowPointer(windowPointer) {
    // seed random number generator
    srand(time(0));

    this->boids = new std::vector<Boid*>();

    // create default number of boids
    for(int i = 0; i < DEFAULT_NUM_BOIDS; i++) {
        Boid* newBoid = new Boid();
        newBoid->setIdNumber(i);
        boids->push_back(newBoid);
    }

    // set random boid velocity
    for(auto boid : *boids) {
        // TODO: change the 100.f speed to a speed constant
        boid->setVelocity(vec2::vecFromDegree(rand() % 360) * BOID_DEFAUL_SPEED);
    }

    // set random boid position
    for(auto boid : *boids) {
        float xPos = rand() % windowPointer->getSize().x;
        float yPos = rand() % windowPointer->getSize().y;

        boid->setPosition(xPos, yPos);
        boid->setBoundPos(xPos - BOID_DEFAULT_BOUNDARY_RADIUS, yPos - BOID_DEFAULT_BOUNDARY_RADIUS);
    }
}

void BoidScreen::update(const sf::Time& dt) {
    for (size_t i=0; i < boids->size(); i++) {
        Boid* boid = (*boids)[i];
        int nborCount = 0;
        float velocityXSum = 0.f;
        float velocityYSum = 0.f;

        int repulseCount = 0;
        float repulsionXSum = 0.f;
        float repulsionYSum = 0.f;

        // Temporary solution to test boundary TODO: Implement grid for spatial partition to improve performance
        for (size_t j=i+1; j < boids->size(); j++) {
            Boid* nborBoid = (*boids)[j];

            // Set velocity of crossed boids to the average
            if (boid->isWithinBoundary(nborBoid->getPosition(), BOID_DEFAULT_BOUNDARY_RADIUS)) {
                nborCount += 1;
                velocityXSum += nborBoid->getVelocity().x;
                velocityYSum += nborBoid->getVelocity().y;

                // std::cout << boid->getIdNumber() << " crossed " << nborBoid->getIdNumber() << "\n"; // TODO delete

                if (boid->isWithinBoundary(nborBoid->getPosition(), FLOCK_DEFAULT_SEPARATION_RADIUS)) {
                    repulseCount += 1;
                    sf::Vector2f positionDiff = boid->getPosition() - nborBoid->getPosition();
                    float distanceBetween = std::max(1.0f, vec2::distanceBetweenPoints(boid->getVelocity(), nborBoid->getVelocity()));
                    
                    repulsionXSum += positionDiff.x / distanceBetween;
                    repulsionYSum += positionDiff.y / distanceBetween;
                }    
            }
        }

        if (nborCount != 0) {
            float averageRepulsionX = repulsionXSum / repulseCount;
            float averageRepulsionY = repulsionYSum / repulseCount;
            float repulseNormalizer = vec2::distanceFormula(averageRepulsionX, 0, averageRepulsionY, 0);

            // boid->setVelocity(sf::Vector2(averageRepulsionX/repulseNormalizer, averageRepulsionY/repulseNormalizer));
            if (repulseCount != 0) {
                boid->setVelocity(sf::Vector2(velocityXSum / nborCount + averageRepulsionX,  velocityYSum / nborCount + averageRepulsionY));
            } else {
                boid->setVelocity(sf::Vector2(velocityXSum / nborCount,  velocityYSum / nborCount));
            }
        }

        boid->update(dt);

        float xPos = boid->getPosition().x;
        float yPos = boid->getPosition().y;

        // wrap boid around screen
        if(boid->getPosition().x < 0) {
            xPos = windowPointer->getSize().x;
            yPos = boid->getPosition().y;
        } else if(boid->getPosition().x > windowPointer->getSize().x) {
            xPos = 0;
            yPos = boid->getPosition().y;
        }

        if(boid->getPosition().y < 0) {
            xPos = boid->getPosition().x;
            yPos = windowPointer->getSize().y;
        } else if(boid->getPosition().y > windowPointer->getSize().y) {
            xPos = boid->getPosition().x;
            yPos = 0;
        }

        boid->setPosition(xPos, yPos);
        boid->setBoundPos(xPos - BOID_DEFAULT_BOUNDARY_RADIUS, yPos - BOID_DEFAULT_BOUNDARY_RADIUS);
    }
}

BoidScreen::~BoidScreen() {
    for(auto boid : *boids) {
        delete boid;
    }
    delete boids;
}
