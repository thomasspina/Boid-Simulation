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

const std::vector<Cell*>& Grid::getCellsInNeighbourhood(Boid* boid) {
    neighbourhoodCellBuffer.clear();
    std::pair<int, int> gridPosition = getGridPositionFromCoords(boid->getPosition());


    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            const int x = gridPosition.first + i;
            const int y = gridPosition.second + j;

            // check if the cell is in the grid
            if (x >= 0 && x < numCols && y >= 0 && y < numRows) {
                neighbourhoodCellBuffer.push_back(&grid[y][x]);
            }
        }
    }

    return neighbourhoodCellBuffer;
}

const std::vector<Boid*>& Grid::getBoidsInNeighbouringCells(Boid* boid) {
    neighbourhoodBoidsBuffer.clear();

    const std::vector<Cell*>& cells = getCellsInNeighbourhood(boid);
    // get the boids in the cells in the boid's radius
    for (Cell* cell : cells) {
        const std::vector<Boid*>& boidsInCell = cell->getBoids();
        neighbourhoodBoidsBuffer.insert(neighbourhoodBoidsBuffer.end(), boidsInCell.begin(), boidsInCell.end());
    }

    return neighbourhoodBoidsBuffer;
}

Cell* Grid::getCellFromPosition(Boid* boid) {
    return getCellFromPosition(boid->getPosition());
}

Cell* Grid::getCellFromPosition(const sf::Vector2f& position) {
    std::pair<int, int> gridPosition = getGridPositionFromCoords(position);

    return &grid[gridPosition.second][gridPosition.first];
}

// returns the cell coordinates of the grid the given coordinates are in
std::pair<int, int> Grid::getGridPositionFromCoords(const sf::Vector2f& position) {
    // get the cell the boid is in. +1 for offset because of offscreen grid
    int x = std::floor(position.x) / SCREEN_GRID_CELL_SIZE;
    int y = std::floor(position.y) / SCREEN_GRID_CELL_SIZE;

    // take negative positions and too big positions into account
    y = (y < 0) ? 0 : (y >= grid.size()) ? numRows - 1 : y;
    x = (x < 0) ? 0 : (x >= grid[y].size()) ? numCols - 1 : x;

    return {x, y};
}