#pragma once

#include "boidScreen.hpp"

class App {
private: 
    // FPS UI graph
    static const int FPS_HISTORY_SIZE = 600;
    float fpsHistory[FPS_HISTORY_SIZE] = {0};
    int fpsOffset = 0;

    // Memory UI graph
    static const int MEMORY_HISTORY_SIZE = 600;
    float memoryHistory[MEMORY_HISTORY_SIZE] = {0};
    int memoryOffset = 0;

    // Config UI toggles boundary visibility
    bool drawBoundary = false;

    double getMemoryUsage() const;

    void drawPerformanceUI();
    void drawConfigUI(BoidScreen& boidScreen);
    void drawUI(BoidScreen& boidScreen);
public:
    App() = default;
    int run();
};