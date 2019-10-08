
#ifndef SCREEN_HH
#define SCREEN_HH

#include <list>

#include "Scene.h"
#include "../EngineObject.h"
#include "../Assets/header/Shape.h"
#include "../Assets/header/Shapes.h"

#include "../../debug.h"

class Screen : public EngineObject, public sf::Drawable {
  protected:
    std::list<Asset *> assets;
    Scene scene;

  public:
    Screen();
    Screen(std::list<Asset *>& assets, Scene& scene);
    ~Screen();

    void event(sf::Event& event) final;
    void event(atreus::Event& event) final;
    void update(const float deltatime) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    virtual void extra_event(sf::Event&) {};
    virtual void extra_event(atreus::Event&) {};
    virtual void extra_update(const float) {};
    virtual void extra_draw(sf::RenderTarget&, sf::RenderStates) const {};
};


#endif // SCREEN_HH
