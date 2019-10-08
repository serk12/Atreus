#ifndef SCENE_HH
#define SCENE_HH

#include "../EngineObject.h"

class Scene : public EngineObject {
  protected:

  public:
    Scene();
    ~Scene();

    void event(sf::Event& event) final;
    void event(atreus::Event& event) final;
    void update(const float deltatime) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    virtual void extra_event(sf::Event&) {};
    virtual void extra_event(atreus::Event&) {};
    virtual void extra_update(const float) {};
    virtual void extra_draw(sf::RenderTarget&, sf::RenderStates) const {};
};

#endif // SCENE_HH
