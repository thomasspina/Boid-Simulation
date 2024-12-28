#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>

#include "boid.hpp"
#include "flockingBehavior.hpp"
#include "constants.hpp"
#include "grid.hpp"

class BoidScreen {
private:
    float maxBoidSpeed = BOID_DEFAULT_MAX_SPEED;
    float minBoidSpeed = BOID_DEFAULT_MIN_SPEED;
    std::vector<uint32_t> colors = {
        0xf9fbf0, 
        0xd1eeff, 
        0x8fc5f4, 
        0x4b89da
    };
    sf::RenderWindow* windowPointer;
    Grid* grid;
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
    int getNumBoids() const { return grid->getNumBoids(); }
    const std::vector<Boid*>& getBoids() const { return grid->getBoids(); }
    float getBoidNeighbourhoodRadius() const { return boidNeighbourhoodRadius; }
    bool getIsAvoidingScreenEdges() const { return isAvoidingScreenEdges; }
    float getMaxBoidSpeed() const { return maxBoidSpeed; }
    Grid* getGrid() { return grid; }

    // setters
    void setNumBoids(const int numBoids);
    void setBoidNeighbourhoodRadius(const float radius);
    void setAvoidScreenEdges(bool avoid) { this->isAvoidingScreenEdges = avoid; }
    void setMaxBoidSpeed(const float speed);
};
