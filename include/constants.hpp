#pragma once

#define SCREEN_WIDTH 1920u
#define SCREEN_HEIGHT 1080u
#define SCREEN_TITLE "Boid Simulator"
#define SCREEN_FPS 60u
#define SCREEN_GRID_CELL_SIZE 100u

#define BOID_SCREEN_DEVIATION_MARGIN 100.f
#define BOID_SCREEN_DEVIATION_TURN_FACTOR 0.1f

#define AVG_MEMORY_USAGE 50.0f

#define DEFAULT_NUM_BOIDS 60
#define MAX_NUM_BOIDS 1000

#define BOID_DEFAULT_RADIUS 5.f // Radius to create boid shape
#define BOID_DEFAULT_COLOR sf::Color::Green
#define BOID_DEFAULT_SPEED 100.f
#define BOID_DEFAULT_MAX_SPEED 150.f
#define BOID_MAXIMUM_MAX_SPEED 400.f
#define BOID_DEFAULT_MIN_SPEED 50.f

#define BOID_DEFAULT_NEIGHBOURHOOD_RADIUS 50.f
#define BOID_MAXIMUM_NEIGHBOURHOOD_RADIUS 200.f
#define BOID_DEFAULT_NEIGHBOURHOOD_COLOR sf::Color(0, 0, 0, 0)
#define BOID_DEFAULT_NEIGHBOURHOOD_OUTLINE_COLOR sf::Color(255, 0, 0, 255)
#define BOID_DEFAULT_NEIGHBOURHOOD_OUTLINE_THICKNESS 1.f

#define FLOCK_DEFAULT_SEPARATION_RADIUS (BOID_DEFAULT_RADIUS + 10.f)
#define FLOCK_MAXIMUM_SEPARATION_RADIUS (BOID_DEFAULT_RADIUS + 30.f)
#define FLOCK_DEFAULT_AVOID_FACTOR 0.1f
#define FLOCK_MAXIMUM_AVOID_FACTOR 1.0f
#define FLOCK_DEFAULT_MATCHING_FACTOR 0.5f
#define FLOCK_MAXIMUM_MATCHING_FACTOR 1.0f
#define FLOCK_DEFAULT_CENTERING_FACTOR 0.1f
#define FLOCK_MAXIMUM_CENTERING_FACTOR 1.0f

#define BOID_DEFAULT_MOUSE_AVOIDANCE_FACTOR 5.0f
#define BOID_DEFAULT_MOUSE_AVOIDANCE_RADIUS (BOID_DEFAULT_NEIGHBOURHOOD_RADIUS * 1.5f)

#define BOID_WANDER_CIRCLE_DISTANCE 50.0f
#define BOID_WANDER_CIRCLE_RADIUS 25.0f
#define BOID_WANDER_ANGLE_CHANGE 0.3f
#define BOID_WANDER_FORCE_FACTOR 1.0f
#define BOID_WANDER_FORCE_FACTOR_MAX 5.0f

#define BOID_DISTANCE_CALCULATION_SCALER 0.01f // Constant used to scale distance influence on boid behavior








