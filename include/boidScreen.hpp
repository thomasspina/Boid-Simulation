#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "boid.hpp"
#include "constants.hpp"

class BoidScreen {
private:
    std::vector<Boid*>* boids;

    sf::RenderWindow* windowPointer;

    void createBoid();
    void wrapAroundScreen(Boid* boid);

    void setRandomBoidVelocity(Boid* boid);
    void setRandomBoidPosition(Boid* boid);
public:
    BoidScreen(sf::RenderWindow* windowPointer);
    ~BoidScreen();
    void update(const sf::Time& dt);

    const std::vector<Boid*>* const getBoids() const { return boids; }
    void setNumBoids(const int numBoids);
    int getNumBoids() const { return boids->size(); }
    void setBoidNeighbourhoodRadius(const float radius);
};