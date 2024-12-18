#pragma once

#include <vector>

#include "boid.hpp"

class BoidScreen {
private:
    std::vector<Boid*>* boids;
public:
    BoidScreen();
    void update(const sf::Time& dt);

    const std::vector<Boid*>* const getBoids() const { return boids; }
};