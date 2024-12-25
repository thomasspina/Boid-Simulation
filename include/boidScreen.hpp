#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "boid.hpp"
#include "constants.hpp"

class BoidScreen {
private:
    std::vector<Boid*>* boids;
    sf::RenderWindow* windowPointer;
    float boidNeighbourhoodRadius = BOID_DEFAULT_BOUNDARY_RADIUS;

    // private helpers
    Boid* createBoid();
    void wrapAroundScreen(Boid* boid);

    void setRandomBoidVelocity(Boid* boid);
    void setRandomBoidPosition(Boid* boid);
public:
    BoidScreen(sf::RenderWindow* windowPointer);
    ~BoidScreen();

    void update(const sf::Time& dt);

    // getters
    const std::vector<Boid*>* const getBoids() const { return boids; }
    int getNumBoids() const { return boids->size(); }
    float getBoidNeighbourhoodRadius() const { return boidNeighbourhoodRadius; }

    // setters
    void setNumBoids(const int numBoids);
    void setBoidNeighbourhoodRadius(const float radius);
};