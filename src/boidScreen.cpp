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
    const float xPos = boid->getPosition().x;
    const float yPos = boid->getPosition().y;

    float vx = boid->getVelocity().x;
    float vy = boid->getVelocity().y;

    const float windowWidth = windowPointer->getSize().x;
    const float windowHeight = windowPointer->getSize().y;

    // check left margin
    if (xPos < BOID_SCREEN_DEVIATION_MARGIN)
        vx = vx + BOID_SCREEN_DEVIATION_TURN_FACTOR * std::abs(BOID_SCREEN_DEVIATION_MARGIN - xPos);

    // check right margin
    else if (xPos > windowWidth - BOID_SCREEN_DEVIATION_MARGIN)
        vx = vx - BOID_SCREEN_DEVIATION_TURN_FACTOR * std::abs(BOID_SCREEN_DEVIATION_MARGIN - (windowWidth - xPos));


    // check top margin
    if (yPos < BOID_SCREEN_DEVIATION_MARGIN)
        vy = vy + BOID_SCREEN_DEVIATION_TURN_FACTOR * std::abs(BOID_SCREEN_DEVIATION_MARGIN - yPos);
    
    // check bottom margin
    else if (yPos > windowHeight - BOID_SCREEN_DEVIATION_MARGIN) 
        vy = vy - BOID_SCREEN_DEVIATION_TURN_FACTOR * std::abs(BOID_SCREEN_DEVIATION_MARGIN - (windowHeight - yPos));

    boid->setVelocity({vx, vy});
}

void BoidScreen::setRandomBoidVelocity(Boid* boid) {
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
    const std::vector<Boid*>& boids = grid->getBoids();
    const sf::Vector2u& windowSize = windowPointer->getSize();

    #if defined(_WIN32)
        const sf::Vector2f& mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
    #elif defined(__APPLE__)
        const sf::Vector2f& mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*windowPointer));
    #endif



    for (size_t i=0; i < getNumBoids(); i++) {
        Boid* boid = boids[i];
        std::vector<Boid*> boidsInNeighbouringCells = grid->getBoidsInNeighbouringCells(boid);

        flockingBehavior.applyMouseAvoidance(boid, mousePos);
        flockingBehavior.applyMouseAvoidance(boid, mousePos);
        flockingBehavior.applyFlockingLogic(boid, boidsInNeighbouringCells, dt);

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