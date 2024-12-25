#include "imgui.h"
#include "imgui-SFML.h"

#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
#elif __APPLE__
    #include <mach/mach.h>
#endif

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "app.hpp"
#include "constants.hpp"
#include "boidScreen.hpp"


double App::getMemoryUsage() const {
    #if defined(_WIN32)
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        
        return static_cast<float>(pmc.WorkingSetSize) / (1024.0f * 1024.0f); // convert to megabytes
    #elif defined(__APPLE__)
        struct task_basic_info t_info;
        mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

        // return 0 if process info returns error kernel return value
        if (KERN_SUCCESS != task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count))
            return 0.0;

        // return process memory usage in MB
        return static_cast<float>(t_info.resident_size) / (1024.0f * 1024.0f); // convert to megabytes
    #endif
}

void App::drawPerformanceUI() {
    float currentFPS = ImGui::GetIO().Framerate;
        
    // update FPS history
    fpsHistory[fpsOffset] = currentFPS;
    fpsOffset = (fpsOffset + 1) % FPS_HISTORY_SIZE;
    
    // draw fps info
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

    float currentMemory = getMemoryUsage();

    // update memory history
    memoryHistory[memoryOffset] = currentMemory;
    memoryOffset = (memoryOffset + 1) % MEMORY_HISTORY_SIZE;

    // draw memory info
    ImGui::Text("Memory Usage: %.2f MB", currentMemory);
    ImGui::PlotLines("RAM", 
        memoryHistory, 
        MEMORY_HISTORY_SIZE, 
        memoryOffset,
        "", 
        0.0f,           
        AVG_MEMORY_USAGE + 20.0f,         
        ImVec2(0, 30)
    );
}

void App::drawConfigUI(BoidScreen& boidScreen) {
    int numBoids = boidScreen.getNumBoids();
    if (ImGui::SliderInt("Number of Boids", &numBoids, 1, MAX_NUM_BOIDS)) {
        boidScreen.setNumBoids(numBoids);
    }

    float neighbourhoodRadius = boidScreen.getBoidNeighbourhoodRadius();
    if (ImGui::SliderFloat("Neighbourhood Radius", &neighbourhoodRadius, BOID_DEFAULT_NEIGHBOURHOOD_RADIUS, BOID_MAXIMUM_NEIGHBOURHOOD_RADIUS)) {
        boidScreen.setBoidNeighbourhoodRadius(neighbourhoodRadius);
    }
    ImGui::Checkbox("Show Boid Neighbourhood", &drawBoundary);
}

void App::drawRulesUI() {
    
}

void App::drawUI(BoidScreen& boidScreen) {
    ImGui::Begin("Boid Menu");

    ImGui::SetWindowPos(ImVec2(1000, 20), ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(350, 700), ImGuiCond_Once);

    ImGui::SetNextItemOpen(true, ImGuiCond_Once); // open menu by default
    if (ImGui::CollapsingHeader("Performance")) {
        drawPerformanceUI();
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once); // open menu by default
    if (ImGui::CollapsingHeader("Configuration")) {
        drawConfigUI(boidScreen);
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once); // open menu by default
    if (ImGui::CollapsingHeader("Rules")) {
        drawRulesUI();
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
    
    // main loop
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

        drawUI(boids);

        /// RENDER WINDOW 

        window.clear();

        // render boids and their boundaries
        for (auto boid : *boids.getBoids()) {
            window.draw(*boid);

            // draw boid boundary if enabled
            if (drawBoundary) {
                window.draw(boid->getBoundary());
            }
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
