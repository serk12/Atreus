#ifndef GAME_HH
#define GAME_HH

#include "../../Engine/header/Engine.h"

class Game : public Engine {
  private:
    std::list<Screen *> screens;

  public:
    void load();
};

#endif // ifndef GAME_HH
