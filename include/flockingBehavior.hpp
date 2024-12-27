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

    FlockingBehavior() = default;
    FlockingBehavior(const FlockingBehavior&) = delete;
    FlockingBehavior& operator=(const FlockingBehavior&) = delete;
public:
    static FlockingBehavior& getInstance() {
        static FlockingBehavior instance;
        return instance;
    }

    void applyFlockingLogic(Boid* boid, std::vector<Boid*>* boids);
    std::pair<float, float> applySeparationLogic(Boid* boid, std::vector<Boid*>* boids);
    std::pair<float, float> applyAlignmentLogic(Boid* boid, std::vector<Boid*>* boids, int& nborCount);
    std::pair<float, float> applyCohesionLogic(Boid* boid, std::vector<Boid*>* boids, int& nborCount);

    // pointer getters
    float* getSeparationRadiusPointer() { return &this->separationRadius; }
    float* getSeparationAvoidFactorPointer() { return &this->separationAvoidFactor; }
    bool* getIsSeparationEnabledPointer() { return &this->separationEnabled; }
};
