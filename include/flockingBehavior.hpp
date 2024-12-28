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

    float separationRadius = FLOCK_DEFAULT_SEPARATION_RADIUS;
    float separationAvoidFactor = FLOCK_DEFAULT_AVOID_FACTOR;
    float matchingFactor = FLOCK_DEFAULT_MATCHING_FACTOR;
    float centeringFactor = FLOCK_DEFAULT_CENTERING_FACTOR;

    FlockingBehavior() = default;
    FlockingBehavior(const FlockingBehavior&) = delete;
    FlockingBehavior& operator=(const FlockingBehavior&) = delete;

    void applySeparationLogic(Boid* currBoid, Boid* nborBoid, float& repulsionXSum, float& repulsionYSum);
    void applyAlignmentLogic(Boid* nborBoidPos, float& avgVelocityX, float& avgVelocityY);
    void applyCohesionLogic(Boid* nborBoidPos, float& avgPosX, float& avgPosY);
public:
    static FlockingBehavior& getInstance() {
        static FlockingBehavior instance;
        return instance;
    }

    void applyFlockingLogic(Boid* boid, const std::vector<Boid*>& boids);

    // pointer getters
    float* getSeparationRadiusPointer() { return &this->separationRadius; }
    float* getSeparationAvoidFactorPointer() { return &this->separationAvoidFactor; }
    float* getMatchingFactorPointer() { return &this->matchingFactor; }
    float* getCenteringFactorPointer() { return &this->centeringFactor; }
    bool* getIsSeparationEnabledPointer() { return &this->separationEnabled; }
    bool* getIsAlignmentEnabledPointer() { return &this->alignmentEnabled; }
    bool* getIsCohesionEnabledPointer() { return &this->cohesionEnabled; }
};
