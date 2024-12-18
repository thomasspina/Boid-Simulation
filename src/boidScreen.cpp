#include "boidScreen.hpp"

#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"

BoidScreen::BoidScreen(sf::RenderWindow* windowPointer) : windowPointer(windowPointer) {
    // seed random number generator
    srand(time(0));

    this->boids = new std::vector<Boid*>();

    // create default number of boids
    for(int i = 0; i < DEFAULT_NUM_BOIDS; i++) {
        boids->push_back(new Boid());
    }

    // set random boid velocity
    for(auto boid : *boids) {
        // TODO: change the 100.f speed to a speed constant
        boid->setVelocity(vec2::vecFromDegree(rand() % 360) * 500.f);
    }

    // set random boid position
    for(auto boid : *boids) {
        boid->setPosition(rand() % windowPointer->getSize().x, rand() % windowPointer->getSize().y);
    }
}

void BoidScreen::update(const sf::Time& dt) {
    for(auto boid : *boids) {
        boid->update(dt);

        // wrap boid around screen
        if(boid->getPosition().x < 0) {
            boid->setPosition(windowPointer->getSize().x, boid->getPosition().y);
        } else if(boid->getPosition().x > windowPointer->getSize().x) {
            boid->setPosition(0, boid->getPosition().y);
        }

        if(boid->getPosition().y < 0) {
            boid->setPosition(boid->getPosition().x, windowPointer->getSize().y);
        } else if(boid->getPosition().y > windowPointer->getSize().y) {
            boid->setPosition(boid->getPosition().x, 0);
        }
    }
}

BoidScreen::~BoidScreen() {
    for(auto boid : *boids) {
        delete boid;
    }
    delete boids;
}