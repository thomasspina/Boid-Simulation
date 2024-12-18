#include "boidScreen.hpp"

#include "boid.hpp"
#include "constants.hpp"

BoidScreen::BoidScreen() {
    // seed random number generator
    srand(time(0));

    this->boids = new std::vector<Boid*>();

    // create default number of boids
    for(int i = 0; i < DEFAULT_NUM_BOIDS; i++) {
        boids->push_back(new Boid());
    }

    // set random boid velocity
    for(auto boid : *boids) {
        boid->setVelocity({static_cast<float>((rand() % 200) - 100), static_cast<float>((rand() % 200) - 100)});
    }

    // set random boid position
    for(auto boid : *boids) {
        boid->setPosition({static_cast<float>(rand() % SCREEN_WIDTH + 1), static_cast<float>(rand() % SCREEN_HEIGHT + 1)});
    }
}

void BoidScreen::update(const sf::Time& dt) {
    for(auto boid : *boids) {
        boid->update(dt);
    }
}