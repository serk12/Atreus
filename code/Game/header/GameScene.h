#ifndef GAMESCENE_HH
#define GAMESCENE_HH

#include "../../Engine/header/Scene.h"

class GameScene : public Scene {};

#endif // ifndef GAMESCENE_HH

#ifndef GAMESCREEN_HH
#define GAMESCREEN_HH

#include "../../Engine/header/Screen.h"

class GameScreen : public Screen {
  public:
    GameScreen() : Screen() {}
    GameScreen(std::list<Asset *>& assets, Scene& scene) : Screen(assets, scene) {}

    void extra_event(sf::Event& event) final
    {
        scene.event(event);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                assets.push_front(new Rectangle());
            }
            else if (event.mouseButton.button == sf::Mouse::Middle) {
                assets.push_front(new Circle());
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                assets.push_front(new Polygon());
            }
        }
    }
};

#endif // ifndef GAMESCREEN_HH
