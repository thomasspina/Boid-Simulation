#pragma once

#include <vector>
#include "boid.hpp"
#include <algorithm>


class flockingBehavior {
public:
    static void applyFlockingLogic(Boid* boid, std::vector<Boid*>* boids);
    // void separation(Boid* boid);
    // void alignment();
    // void cohesion();
};
