#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "cell.hpp"
#include "boid.hpp"

class Grid {
private:
    int numCols;
    int numRows;

    std::vector<std::vector<Cell>> grid;
    std::vector<Boid*> boids;
public:
    Grid(sf::Window* window);
    ~Grid();

    void addBoid(Boid* boid);
    void update();
    Boid* popLastBoid();

    std::vector<Cell*> getCellsInNeighbourhood(Boid* boid);
    std::vector<Boid*> getBoidsInNeighbouringCells(Boid* boid);
    Cell* getCellFromPosition(Boid* boid);
    Cell* getCellFromPosition(const sf::Vector2f& position);

    std::vector<Boid*>& getBoids() { return boids; }
    const std::vector<Boid*>& getBoids() const { return boids; }
    int getNumBoids() const { return boids.size(); }
    std::vector<std::vector<Cell>>& getGrid() { return grid; }
};