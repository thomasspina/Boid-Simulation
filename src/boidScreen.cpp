#include "boidScreen.hpp"

#include "boid.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include "flockingBehavior.hpp"

Boid* BoidScreen::createBoid() {
    Boid* newBoid = new Boid();
    newBoid->setIdNumber(this->boids->size());
    this->boids->push_back(newBoid);

    // set random boid velocity
    setRandomBoidVelocity(newBoid);

    // set random boid position
    setRandomBoidPosition(newBoid);

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
    float xPos = boid->getPosition().x;
    float yPos = boid->getPosition().y;

    float vx = boid->getVelocity().x;
    float vy = boid->getVelocity().y;

    // check left margin
    if (xPos < BOID_SCREEN_DEVIATION_MARGIN)
        vx = boid->getVelocity().x + BOID_SCREEN_DEVIATION_TURN_FACTOR;

    // check right margin
    else if (xPos > windowPointer->getSize().x - BOID_SCREEN_DEVIATION_MARGIN)
        vx = boid->getVelocity().x - BOID_SCREEN_DEVIATION_TURN_FACTOR;


    // check top margin
    if (yPos < BOID_SCREEN_DEVIATION_MARGIN)
        vy = boid->getVelocity().y + BOID_SCREEN_DEVIATION_TURN_FACTOR;
    
    // check bottom margin
    else if (yPos > windowPointer->getSize().y - BOID_SCREEN_DEVIATION_MARGIN) 
        vy = boid->getVelocity().y - BOID_SCREEN_DEVIATION_TURN_FACTOR;

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

    this->boids = new std::vector<Boid*>();

    // create default number of boids
    for(int i = 0; i < DEFAULT_NUM_BOIDS; i++) {
        createBoid();
    }
}

BoidScreen::~BoidScreen() {
    for(auto boid : *boids) {
        delete boid;
    }
    delete boids;
}

void BoidScreen::update(const sf::Time& dt) {
    for (size_t i=0; i < boids->size(); i++) {
        Boid* boid = (*boids)[i];
        
        flockingBehavior.applyFlockingLogic(boid, boids);

        boid->update(dt);
        
        if (!isAvoidingScreenEdges)
            wrapAroundScreen(boid);
        else
            deviateBoidFromScreenBoundary(boid);
    }
}

void BoidScreen::setBoidNeighbourhoodRadius(const float radius) {
    this->boidNeighbourhoodRadius = radius;
    for (auto boid : *boids) {
        boid->setNeighboorhoodRadius(boidNeighbourhoodRadius);
    }
}

void BoidScreen::setNumBoids(const int newNumBoids) {
    int numBoids = this->boids->size();

    // delete boids if new number of boids is less than current number
    for (int i = numBoids; i > newNumBoids; i--) {
        delete this->boids->back();
        this->boids->pop_back();
    }

    // create new boids if new number of boids is greater than current number
    for (int i = numBoids; i <= newNumBoids; i++) {
        Boid* newBoid = createBoid();
        newBoid->setNeighboorhoodRadius(boidNeighbourhoodRadius);
    }
}