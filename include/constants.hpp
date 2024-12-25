#pragma once

#define SCREEN_WIDTH 1920u
#define SCREEN_HEIGHT 1080u
#define SCREEN_TITLE "Boid Simulator"
#define SCREEN_FPS 60u

#define BOID_SCREEN_DEVIATION_MARGIN 50.f
#define BOID_SCREEN_DEVIATION_TURN_FACTOR 0.5f

#define AVG_MEMORY_USAGE 50.0f // TODO: is there a better way of getting this value?

#define DEFAULT_NUM_BOIDS 30
#define MAX_NUM_BOIDS 100

#define BOID_DEFAULT_RADIUS 5.f // Radius to create boid shape
#define BOID_DEFAULT_COLOR sf::Color::Green
#define BOID_DEFAULT_SPEED 100.f
#define BOID_DEFAULT_MAX_SPEED 150.f
#define BOID_DEFAULT_MIN_SPEED 50.f

#define BOID_DEFAULT_NEIGHBOURHOOD_RADIUS (BOID_DEFAULT_RADIUS + 100.f)
#define BOID_MAXIMUM_NEIGHBOURHOOD_RADIUS (BOID_DEFAULT_RADIUS + 200.f)
#define BOID_DEFAULT_NEIGHBOURHOOD_COLOR sf::Color(0, 0, 0, 0)
#define BOID_DEFAULT_NEIGHBOURHOOD_OUTLINE_COLOR sf::Color(255, 0, 0, 255)
#define BOID_DEFAULT_NEIGHBOURHOOD_OUTLINE_THICKNESS 1.f

#define FLOCK_DEFAULT_SEPARATION_RADIUS (BOID_DEFAULT_RADIUS + 20.f)
#define FLOCK_DEFAULT_AVOID_FACTOR 1
#define FLOCK_DEFAULT_MATCHING_FACTOR 0.5
#define FLOCK_DEFAULT_CENTERING_FACTOR 0.3









