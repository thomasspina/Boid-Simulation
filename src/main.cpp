#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "boid.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1920u, 1080u}), "Boids");
    window.setFramerateLimit(60);
    if(!ImGui::SFML::Init(window)) return -1;

    auto boidPtr = std::make_unique<Boid>();

    sf::Clock deltaClock;
    while (window.isOpen()) {

        // Handle UI events
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        boidPtr->update(deltaClock.getElapsedTime());

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::ShowDemoWindow();

        // update frame
        window.clear();
        window.draw(*(boidPtr.get()));
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}