#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream> // TODO: remove this. This is for debugging

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "app.hpp"
#include "constants.hpp"
#include "boidScreen.hpp"

int App::run() {
    // Initialize window
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), SCREEN_TITLE);
    window.setFramerateLimit(SCREEN_FPS); 
    if(!ImGui::SFML::Init(window)) return -1;

    // Initialize boid screen where all boids will be rendered
    BoidScreen boids = BoidScreen(&window);

    sf::Clock dtC;

    // Main loop
    while (window.isOpen()) {
        // retrieve current frame elapsed time
        auto currDeltaTime = dtC.restart();

        // reset delta time clock
        ImGui::SFML::Update(window, currDeltaTime);

        window.clear();

        sf::Event event;
        while (window.pollEvent(event)) {
            // ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
        }

        // ImGui::ShowDemoWindow(); // TODO: remove demo window

        // update boids
        boids.update(currDeltaTime);

        // render boids
        for (auto boid : *boids.getBoids()) {
            window.draw(*boid);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
