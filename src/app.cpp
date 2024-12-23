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

void App::drawPerformanceUI() {
    float currentFPS = ImGui::GetIO().Framerate;
        
    // Update FPS history
    fpsHistory[fpsOffset] = currentFPS;
    fpsOffset = (fpsOffset + 1) % FPS_HISTORY_SIZE;
    
    ImGui::Text("Frames Per Second (FPS) : %.1f", currentFPS);
    ImGui::Text("Application average %.3f ms/frame", 1000.0f / currentFPS);
    ImGui::PlotLines("FPS", 
        fpsHistory, 
        FPS_HISTORY_SIZE, 
        fpsOffset,
        "", 
        0.0f,           
        SCREEN_FPS + 10.0f,         
        ImVec2(0, 30)
    );

    ImGui::Separator();

    
}

void App::drawUI() {
    ImGui::Begin("Boid Menu");

    ImGui::SetWindowPos(ImVec2(1000, 20), ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(320, 700), ImGuiCond_Once);

    if (ImGui::CollapsingHeader("Performance")) {
        drawPerformanceUI();
    }

    ImGui::End();
}

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

        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
        }

        // update boids
        boids.update(currDeltaTime);

        // reset delta time clock
        ImGui::SFML::Update(window, currDeltaTime);


        /// DRAW MENU

        drawUI();

        

        /// RENDER WINDOW 

        window.clear();

        // render boids and their boundaries
        for (auto boid : *boids.getBoids()) {
            window.draw(*boid);

            window.draw(boid->getBoundary());
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
