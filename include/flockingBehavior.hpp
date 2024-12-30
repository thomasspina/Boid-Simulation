#pragma once

#include <vector>
#include <algorithm>
#include <utility> 

#include "boid.hpp"

// Singleton class to handle flocking behavior
class FlockingBehavior {
private: 
    bool separationEnabled = true;
    bool alignmentEnabled = true;
    bool cohesionEnabled = true;
    bool wanderEnabled = true;
    bool mouseAvoidanceEnabled = false;

    float separationRadius = FLOCK_DEFAULT_SEPARATION_RADIUS;
    float separationAvoidFactor = FLOCK_DEFAULT_AVOID_FACTOR;
    float matchingFactor = FLOCK_DEFAULT_MATCHING_FACTOR;
    float centeringFactor = FLOCK_DEFAULT_CENTERING_FACTOR;
    float wanderFactor = BOID_WANDER_FORCE_FACTOR;

    FlockingBehavior() = default;
    FlockingBehavior(const FlockingBehavior&) = delete;
    FlockingBehavior& operator=(const FlockingBehavior&) = delete;

    void applySeparationLogic(const sf::Vector2f& currBoidPos, const sf::Vector2f& nborBoidPos, float& repulsionXSum, float& repulsionYSum);
    void applyAlignmentLogic(const sf::Vector2f& nborVel, float& avgVelocityX, float& avgVelocityY);
    void applyCohesionLogic(const sf::Vector2f& nborBoidPos, float& avgPosX, float& avgPosY);
    void applyWanderLogic(Boid* boid, const sf::Time& dT);

    void applyMouseAvoidanceLogic(Boid* currBoid, const sf::Vector2f& mousePos, float& currX, float& currY);
public:
    static FlockingBehavior& getInstance() {
        static FlockingBehavior instance;
        return instance;
    }

    void applyFlockingLogic(Boid* boid, const std::vector<Boid*>& boids, const sf::Time& dT);
    void applyMouseAvoidance(Boid* currBoid, sf::Vector2f mousePos);

    // pointer getters
    float* getSeparationRadiusPointer() { return &this->separationRadius; }
    float* getSeparationAvoidFactorPointer() { return &this->separationAvoidFactor; }
    float* getMatchingFactorPointer() { return &this->matchingFactor; }
    float* getCenteringFactorPointer() { return &this->centeringFactor; }
    float* getWanderFactorPointer() { return &this->wanderFactor; }
    bool* getIsSeparationEnabledPointer() { return &this->separationEnabled; }
    bool* getIsAlignmentEnabledPointer() { return &this->alignmentEnabled; }
    bool* getIsCohesionEnabledPointer() { return &this->cohesionEnabled; }
    bool* getIsWanderEnabledPointer() { return &this->wanderEnabled; }
    bool* getIsMouseAvoidanceEnabledPointer() { return &this->mouseAvoidanceEnabled; }
};