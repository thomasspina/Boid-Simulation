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
        0xb3f7ff, 
        0xeffafe, 
        0xdbd1ed, 
        0xcfabff
    };
    // std::vector<sf::Color> colors = {
    //     sf::Color(0xc22860), 
    //     sf::Color(0xae2357), 
    //     sf::Color(0x750809), 
    //     sf::Color(0xffedd5)
    // };
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
