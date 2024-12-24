#pragma once

#include "boidScreen.hpp"

class App {
private: 
    static const int FPS_HISTORY_SIZE = 600;
    float fpsHistory[FPS_HISTORY_SIZE] = {0};
    int fpsOffset = 0;

    static const int MEMORY_HISTORY_SIZE = 600;
    float memoryHistory[MEMORY_HISTORY_SIZE] = {0};
    int memoryOffset = 0;

    bool drawBoundary = false;

    double getMemoryUsage() const;
    void drawPerformanceUI();
    void drawConfigUI(BoidScreen& boidScreen);
    void drawUI(BoidScreen& boidScreen);
public:
    App() = default;
    int run();
};