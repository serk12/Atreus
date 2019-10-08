#ifndef GAME_HH
#define GAME_HH

#include "../../Engine/header/Engine.h"
#include "GameScene.h"
class Game : public Engine {
  private:
    void init();
    std::list<Screen *> screens;

  public:
    void load();
};

#endif // ifndef GAME_HH
