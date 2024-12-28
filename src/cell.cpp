#include "cell.hpp"

Cell::Cell(const std::pair<float, float>& topLeftCorner, const std::pair<float, float>& bottomRightCorner) 
: topLeft(topLeftCorner), bottomRight(bottomRightCorner) {
    this->setPosition(topLeft.first, topLeft.second);
    this->setSize(sf::Vector2f(bottomRight.first - topLeft.first, bottomRight.second - topLeft.second));
    this->setFillColor(sf::Color::Transparent);
    this->setOutlineColor(sf::Color::White);
    this->setOutlineThickness(1);
}

void Cell::removeBoid(Boid* boid) {
    auto it = std::find(boids.begin(), boids.end(), boid);
    if (it != boids.end()) {
        boids.erase(it);
    }
}

bool Cell::cellIsWithinBoidNeighbourhood(Boid* boid) {
    const sf::Vector2f& boidPos = boid->getPosition();
    const float boidNeighbourhoodRadius = boid->getNeighbourhoodRadius();

    float distanceX = boidPos.x - std::clamp(boidPos.x, topLeft.first, bottomRight.first);
    float distanceY = boidPos.y - std::clamp(boidPos.y, topLeft.second, bottomRight.second);

    // avoid sqrt by squaring the radius
    return (distanceX * distanceX + distanceY * distanceY) <= (boidNeighbourhoodRadius * boidNeighbourhoodRadius);
}

bool Cell::cellContainsBoidCoords(Boid* boid) const {
    const sf::Vector2f& boidPos = boid->getPosition();
    return boidPos.x >= topLeft.first && boidPos.x <= bottomRight.first && boidPos.y >= topLeft.second && boidPos.y <= bottomRight.second;
}