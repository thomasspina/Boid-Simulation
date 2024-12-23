#pragma once

class App {
private: 
    static const int FPS_HISTORY_SIZE = 600;
    float fpsHistory[FPS_HISTORY_SIZE] = {0};
    int fpsOffset = 0;


    void drawPerformanceUI();
    void drawUI();
public:
    App() = default;
    int run();
};