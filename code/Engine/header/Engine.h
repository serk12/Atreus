#ifndef ENGINE_HH
#define ENGINE_HH

#include "EngineConf.h"
#include "../EngineObject.h"
#include "Screen.h"

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

  protected:
    void setScreen(Screen *screen);

  public:
    Engine();
    ~Engine();
    void start();
};

#endif // ifndef ENGINE_HH
