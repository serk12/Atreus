#ifndef ENGINE_HH
#define ENGINE_HH

#include "EngineConf.h"
#include "EngineObject.h"
#include "Screen.h"
#include "../../debug.h"

class Engine : public EngineConf {
private:
    static const float timeClamp;
    float accumulator;


    sf::RenderWindow window;
    sf::Clock clock;

    Screen *currentScreen;

    void event_();
    void update_();
    void draw_();

public:
    static float fps;
    static float dt;

    Engine();
    ~Engine();
    void start();
};

#endif // ifndef ENGINE_HH
