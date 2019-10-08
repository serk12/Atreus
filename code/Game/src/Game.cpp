#include "../header/Game.h"

void Game::init()
{
    std::list<Asset *> assets;
    assets.push_front(new Rectangle(0));
    GameScene scene;
    screens.push_back(new GameScreen(assets, scene));
}

void Game::load()
{
    init();
    this->setScreen(*(screens.begin()));
    this->start();
}
