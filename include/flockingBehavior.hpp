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

    void setSeparationEnabled(bool enabled) { this->separationEnabled = enabled; }
    void setAlignmentEnabled(bool enabled) { this->alignmentEnabled = enabled; }
    void setCohesionEnabled(bool enabled) { this->cohesionEnabled = enabled; }
};
