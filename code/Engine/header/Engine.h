#ifndef ENGINE_HH
#define ENGINE_HH

#include "EngineObject.h"
#include "Screen.h"
#include "../../utils.h"
#include "../../debug.h"

class Engine : public EngineObject {
private:
    static const float fps;
    static const float dt;
    static const float timeClamp;
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
