#pragma once

class App {
private: 
    static const int FPS_HISTORY_SIZE = 600;
    float fpsHistory[FPS_HISTORY_SIZE] = {0};
    int fpsOffset = 0;

    static const int MEMORY_HISTORY_SIZE = 600;
    float memoryHistory[MEMORY_HISTORY_SIZE] = {0};
    int memoryOffset = 0;

    double getMemoryUsage() const;
    void drawPerformanceUI();
    void drawUI();
public:
    App() = default;
    int run();
};