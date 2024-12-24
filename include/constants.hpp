#pragma once

#define SCREEN_WIDTH 1920u
#define SCREEN_HEIGHT 1080u
#define SCREEN_TITLE "Boid Sim"
#define SCREEN_FPS 60u

#define AVG_MEMORY_USAGE 50.0f // TODO: is there a better way of getting this value?

#define DEFAULT_NUM_BOIDS 30
#define MAX_NUM_BOIDS 100

#define BOID_DEFAULT_RADIUS 15.f
#define BOID_DEFAULT_COLOR sf::Color::Green
#define BOID_DEFAULT_SPEED 300.f
#define BOID_DEFAULT_MAX_SPEED 350.f
#define BOID_DEFAULT_MIN_SPEED 250.f

#define BOID_DEFAULT_BOUNDARY_RADIUS (BOID_DEFAULT_RADIUS + 70.f)
#define BOID_DEFAULT_BOUNDARY_COLOR sf::Color(0, 0, 0, 0) // Remove last zero for visibility
#define BOID_DEFAULT_BOUNDARY_OUTLINE_COLOR sf::Color(255, 0, 0, 0) // Remove last zero for visibility
#define BOID_DEFAULT_BOUNDARY_OUTLINE_THICKNESS 1.f

#define FLOCK_DEFAULT_SEPARATION_RADIUS (BOID_DEFAULT_RADIUS + 40.f)
#define FLOCK_DEFAULT_AVOID_FACTOR 1.2







