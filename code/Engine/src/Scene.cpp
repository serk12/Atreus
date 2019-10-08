#include "../header/Scene.h"

Scene::Scene()
{}

Scene::~Scene() {}

void Scene::event(sf::Event& event)
{
    extra_event(event);
}

void Scene::event(atreus::Event& event)
{
    extra_event(event);
}

void Scene::update(const float deltatime)
{
    extra_update(deltatime);
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    extra_draw(target, states);
}
