#include "../header/Game.h"

void Game::load()
{
    std::list<Asset *> assets;
    assets.push_front(new Rectangle(0));
    Scene   scene;
    Screen *level0 = new Screen(assets, scene);
    this->setScreen(level0);
    this->start();
}
