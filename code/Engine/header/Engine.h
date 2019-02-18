#ifndef ENGINE_HH
#define ENGINE_HH

#include "EngineObject.h"
#include "Screen.h"
#include "../../utils.h"
#include "../../debug.h"

class Engine : public EngineObject {
private:
    static const float fps = 100;
    static const df        = 1 / fps;
    static const timeClamp = 0.2f;
    float accumulator;


    sf::RenderWindow window;
    sf::Clock clock;

    Screen *currentScreen;

    void event_();
    void update_();
    void draw_();

public:
    Engine();
    ~Engine();
    void start();
};

#endif // ifndef ENGINE_HH
