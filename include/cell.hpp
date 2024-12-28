#pragma once

#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

#include "boid.hpp"

class Cell : public sf::RectangleShape {
private:
    std::vector<Boid*> boids = {};

    std::pair<float, float> topLeft = {0.f, 0.f};
    std::pair<float, float> bottomRight = {0.f, 0.f};
public:
    Cell() = default;
    Cell(const std::pair<float, float>& topLeftCorner, const std::pair<float, float>& bottomRightCorner);

    void addBoid(Boid* boid) { boids.push_back(boid); }
    void  removeBoid(Boid* boid);

    bool cellIsWithinBoidNeighbourhood(Boid* boid);
    bool cellContainsBoidCoords(Boid* boid) const;

    const std::vector<Boid*>& getBoids() const { return boids; }
};