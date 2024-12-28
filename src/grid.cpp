#include "grid.hpp"

#include <iostream> // TODO: remove for debugging only

#include "utils.hpp"

Grid::Grid(sf::Window* window) {
    // calculate the number of cells needed to cover the screen (+1 for padding to make sure all boids are in a cell)
    this->numCols = window->getSize().x / SCREEN_GRID_CELL_SIZE + 1;
    this->numRows = window->getSize().y / SCREEN_GRID_CELL_SIZE + 1;

    // initialize the grid with cells
    grid.resize(numRows);
    for (int i = 0; i < this->numRows; i++) {
        grid[i].resize(numCols);
        for (int j = 0; j < this->numCols; j++) {
            std::pair<float, float> topLeft = {j * SCREEN_GRID_CELL_SIZE, i * SCREEN_GRID_CELL_SIZE};
            std::pair<float, float> bottomRight = {(j + 1) * SCREEN_GRID_CELL_SIZE, (i + 1) * SCREEN_GRID_CELL_SIZE};
            grid[i][j] = Cell(topLeft, bottomRight);
        }
    }
}

Grid::~Grid() {
    // delete all boids
    for (Boid* boid : boids) {
        delete boid;
    }
}

void Grid::addBoid(Boid* boid) {
    boids.push_back(boid);

    // add boid to the cell it is in
    getCellFromPosition(boid)->addBoid(boid);
}

void Grid::update() {
    for (std::vector<Cell>& cellRow : grid) {
        for (Cell& cell : cellRow) {
            for (Boid* boid : cell.getBoids()) {
                // update the boid's cell
                Cell* newCell = getCellFromPosition(boid);
                if (newCell != &cell) {
                    cell.removeBoid(boid);
                    newCell->addBoid(boid);
                }
            }
            
        }
    }
}

Boid* Grid::popLastBoid() {
    Boid* boid = boids.back();
    boids.pop_back();
    getCellFromPosition(boid)->removeBoid(boid);
    return boid;
}

std::vector<Cell*> Grid::getCellsInNeighbourhood(Boid* boid) {
    std::vector<Cell*> cells;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int x = boid->getPosition().x / SCREEN_GRID_CELL_SIZE + i;
            int y = boid->getPosition().y / SCREEN_GRID_CELL_SIZE + j;

            // take negative positions and too big positions into account
            y = (y < 0) ? 0 : (y >= grid.size()) ? numRows - 1 : y;
            x = (x < 0) ? 0 : (x >= grid[y].size()) ? numCols - 1 : x;

            cells.push_back(&grid[y][x]);
        }
    }

    return cells;
}

std::vector<Boid*> Grid::getBoidsInNeighbouringCells(Boid* boid) {
    std::vector<Boid*> boidsInNeighbourhood;

    // get the boids in the cells in the boid's radius
    for (Cell* cell : getCellsInNeighbourhood(boid)) {
        for (Boid* boid : cell->getBoids()) {
            boidsInNeighbourhood.push_back(boid);
        }
    }

    return boidsInNeighbourhood;
}

Cell* Grid::getCellFromPosition(Boid* boid) {
    return getCellFromPosition(boid->getPosition());
}

Cell* Grid::getCellFromPosition(const sf::Vector2f& position) {
    // get the cell the boid is in. +1 for offset because of offscreen grid
    int x = std::floor(position.x) / SCREEN_GRID_CELL_SIZE;
    int y = std::floor(position.y) / SCREEN_GRID_CELL_SIZE;

    // take negative positions and too big positions into account
    y = (y < 0) ? 0 : (y >= grid.size()) ? numRows - 1 : y;
    x = (x < 0) ? 0 : (x >= grid[y].size()) ? numCols - 1 : x;

    return &grid[y][x];
}