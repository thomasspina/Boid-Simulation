#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "boid.hpp"
#include "constants.hpp"

class BoidScreen {
private:
    int numBoids = DEFAULT_NUM_BOIDS;
    std::vector<Boid*>* boids;

    sf::RenderWindow* windowPointer;

public:
    BoidScreen(sf::RenderWindow* windowPointer);
    ~BoidScreen();
    void update(const sf::Time& dt);

    const std::vector<Boid*>* const getBoids() const { return boids; }
};