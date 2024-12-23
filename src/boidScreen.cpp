#include "boidScreen.hpp"

#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include "flockingBehavior.hpp"

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
        boid->setVelocity(vec2::vecFromDegree(rand() % 360) * BOID_DEFAUL_SPEED);
    }

    // set random boid position
    for(auto boid : *boids) {
        float xPos = rand() % windowPointer->getSize().x;
        float yPos = rand() % windowPointer->getSize().y;

        boid->setPosition(xPos, yPos);
        // boid->setBoundPos(xPos - BOID_DEFAULT_BOUNDARY_RADIUS, yPos - BOID_DEFAULT_BOUNDARY_RADIUS);
        boid->setBoundPos(xPos, yPos);
    }
}

// TODO: Move all flock behavior to separate class
void BoidScreen::update(const sf::Time& dt) {
    for (size_t i=0; i < boids->size(); i++) {
        Boid* boid = (*boids)[i];
        
        flockingBehavior::applyFlockingLogic(boid, boids);

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
        boid->setBoundPos(xPos, yPos);
        // boid->setBoundPos(xPos - BOID_DEFAULT_BOUNDARY_RADIUS, yPos - BOID_DEFAULT_BOUNDARY_RADIUS);
    }
}

BoidScreen::~BoidScreen() {
    for(auto boid : *boids) {
        delete boid;
    }
    delete boids;
}
