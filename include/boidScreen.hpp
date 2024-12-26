#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>

#include "boid.hpp"
#include "flockingBehavior.hpp"
#include "constants.hpp"

class BoidScreen {

private:
    std::vector<Boid*>* boids;
    std::vector<uint32_t> colors = {
        0xf9fbf0, 
        0xd1eeff, 
        0x8fc5f4, 
        0x4b89da
    };
    sf::RenderWindow* windowPointer;
    float boidNeighbourhoodRadius = BOID_DEFAULT_NEIGHBOURHOOD_RADIUS;
    FlockingBehavior& flockingBehavior = FlockingBehavior::getInstance();
    bool isAvoidingScreenEdges = false;

    // private helpers
    Boid* createBoid();
    void wrapAroundScreen(Boid* boid);
    void deviateBoidFromScreenBoundary(Boid* boid);

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
    bool getIsAvoidingScreenEdges() const { return isAvoidingScreenEdges; }

    // setters
    void setNumBoids(const int numBoids);
    void setBoidNeighbourhoodRadius(const float radius);
    void setAvoidScreenEdges(bool avoid) { this->isAvoidingScreenEdges = avoid; }
};
