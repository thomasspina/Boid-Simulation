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
        // TODO: change the 10.f speed to a var
        //boid->setVelocity(vec2::vecFromDegree(rand() % 360) * 10.f);
    }

    // set random boid position
    for(auto boid : *boids) {
        boid->setPosition(rand() % windowPointer->getSize().x, rand() % windowPointer->getSize().y);
    }
}

void BoidScreen::update(const sf::Time& dt) {
    for(auto boid : *boids) {
        boid->update(dt);
    }
}