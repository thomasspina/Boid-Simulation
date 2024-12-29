#include "boidScreen.hpp"

#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include "flockingBehavior.hpp"
#include <iostream>

Boid* BoidScreen::createBoid() {
    Boid* newBoid = new Boid();
    newBoid->setIdNumber(this->getNumBoids());
    newBoid->setMaxSpeed(maxBoidSpeed);

    int randColor = rand() % colors.size();

    newBoid->setFillColor(colour::HexToColour(colors[randColor]));
    newBoid->setNeighboorhoodRadius(boidNeighbourhoodRadius);

    // set random boid velocity
    setRandomBoidVelocity(newBoid);

    // set random boid position
    setRandomBoidPosition(newBoid);
    
    grid->addBoid(newBoid);

    return newBoid;
}

void BoidScreen::wrapAroundScreen(Boid* boid) {
        float xPos = boid->getPosition().x;
        float yPos = boid->getPosition().y;

        // set x if boid is out of bounds
        if(boid->getPosition().x < 0) {
            xPos = windowPointer->getSize().x;
            yPos = boid->getPosition().y;
        } else if(boid->getPosition().x > windowPointer->getSize().x) {
            xPos = 0;
            yPos = boid->getPosition().y;
        }

        // set y if boid is out of bounds
        if(boid->getPosition().y < 0) {
            xPos = boid->getPosition().x;
            yPos = windowPointer->getSize().y;
        } else if(boid->getPosition().y > windowPointer->getSize().y) {
            xPos = boid->getPosition().x;
            yPos = 0;
        }

        boid->setPosition(xPos, yPos);
        boid->setBoundPos(xPos, yPos);
}

void BoidScreen::deviateBoidFromScreenBoundary(Boid* boid) {
    // TODO: fix formulas (find better ones)
    float xPos = boid->getPosition().x;
    float yPos = boid->getPosition().y;

    float vx = boid->getVelocity().x;
    float vy = boid->getVelocity().y;

    // check left margin
    if (xPos < BOID_SCREEN_DEVIATION_MARGIN)
        vx = boid->getVelocity().x + BOID_SCREEN_DEVIATION_TURN_FACTOR * maxBoidSpeed;

    // check right margin
    else if (xPos > windowPointer->getSize().x - BOID_SCREEN_DEVIATION_MARGIN)
        vx = boid->getVelocity().x - BOID_SCREEN_DEVIATION_TURN_FACTOR * maxBoidSpeed;


    // check top margin
    if (yPos < BOID_SCREEN_DEVIATION_MARGIN)
        vy = boid->getVelocity().y + BOID_SCREEN_DEVIATION_TURN_FACTOR * maxBoidSpeed;
    
    // check bottom margin
    else if (yPos > windowPointer->getSize().y - BOID_SCREEN_DEVIATION_MARGIN) 
        vy = boid->getVelocity().y - BOID_SCREEN_DEVIATION_TURN_FACTOR * maxBoidSpeed;

    boid->setVelocity({vx, vy});
}

void BoidScreen::setRandomBoidVelocity(Boid* boid) {
    // TODO: find a better way to generate random speed
    float randomSpeed = rand() % (int) BOID_DEFAULT_MAX_SPEED;
    if(randomSpeed < BOID_DEFAULT_MIN_SPEED) {
        randomSpeed += BOID_DEFAULT_MIN_SPEED;
    }
    boid->setSpeed(randomSpeed);


    sf::Vector2f random_dir = vec2::vecFromDegree(rand() % 360);
    boid->setVelocity(random_dir * boid->getSpeed());
}

void BoidScreen::setRandomBoidPosition(Boid* boid) {
    float xPos = rand() % windowPointer->getSize().x;
    float yPos = rand() % windowPointer->getSize().y;

    boid->setPosition(xPos, yPos);
    boid->setBoundPos(xPos, yPos);
}

BoidScreen::BoidScreen(sf::RenderWindow* windowPointer) : windowPointer(windowPointer) {
    // seed random number generator
    srand(time(0));

    this->grid = new Grid(windowPointer);

    // create default number of boids
    for(int i = 0; i < DEFAULT_NUM_BOIDS; i++) {
        createBoid();
    }
}

BoidScreen::~BoidScreen() {
    delete grid;
}

void BoidScreen::update(const sf::Time& dt) {
    std::vector<Boid*>& boids = grid->getBoids();
    sf::Vector2f position = static_cast<sf::Vector2f>(sf::Mouse::getPosition());

    for (size_t i=0; i < getNumBoids(); i++) {
        Boid* boid = boids[i];
        std::vector<Boid*> boidsInNeighbouringCells = grid->getBoidsInNeighbouringCells(boid);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            flockingBehavior.applyMouseAvoidance(boid, position);
        }

        flockingBehavior.applyFlockingLogic(boid, boidsInNeighbouringCells);

        boid->update(dt);
        
        if (!isAvoidingScreenEdges)
            wrapAroundScreen(boid);
        else
            deviateBoidFromScreenBoundary(boid);

        // update grid last
        grid->update();
    }
}

void BoidScreen::setBoidNeighbourhoodRadius(const float radius) {
    this->boidNeighbourhoodRadius = radius;
    for (auto boid : grid->getBoids()) {
        boid->setNeighboorhoodRadius(boidNeighbourhoodRadius);
    }
}

void BoidScreen::setNumBoids(const int newNumBoids) {
    int numBoids = grid->getNumBoids();

    // delete boids if new number of boids is less than current number
    for (int i = numBoids; i > newNumBoids; i--) {
        delete grid->popLastBoid();
    }

    // create new boids if new number of boids is greater than current number
    for (int i = numBoids; i <= newNumBoids; i++) {
        createBoid();
    }
}

void BoidScreen::setMaxBoidSpeed(const float speed) {
    this->maxBoidSpeed = speed;
    for (auto boid : grid->getBoids()) {
        boid->setMaxSpeed(maxBoidSpeed);
    }
}
