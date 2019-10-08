#include "../header/Screen.h"

Screen::Screen() {}
Screen::Screen(std::list<Asset *>& assets, Scene& scene)
{
    this->assets = assets;
    this->scene  = scene;
}
Screen::~Screen()
{
    for (std::list<Asset *>::iterator itAsset = assets.begin(); itAsset != assets.end(); ++itAsset) {
        delete (*itAsset);
    }
}

void Screen::event(atreus::Event& event)
{
    if (event.type == atreus::Event::EventType::Collision) {
        Shape::resolveCollision(*event.collisionData.A, *event.collisionData.B, event.collisionData.n, event.collisionData.contact);
        event.collisionData.A->event(event);
        event.collisionData.B->event(event);
    }

    extra_event(event);
}

void Screen::event(sf::Event& event)
{
    for (std::list<Asset *>::iterator itAsset = assets.begin(); itAsset != assets.end(); ++itAsset) {
        (*itAsset)->event(event);
    }

    extra_event(event);
}

void Screen::update(const float deltatime)
{
    for (std::list<Asset *>::iterator itAsset = assets.begin(); itAsset != assets.end(); ++itAsset) {
        Asset *asset = *itAsset;
        asset->update(deltatime);
        std::list<Asset *>::iterator itAssetCol = itAsset;
        ++itAssetCol;
        for (; itAssetCol != assets.end(); ++itAssetCol) {
            Asset *assetCol = *itAssetCol;
            Shape *A        = dynamic_cast<Shape *>(asset);
            Shape *B        = dynamic_cast<Shape *>(assetCol);
            if (Shape::broadDetection(*A, *B) and Shape::narrowDetection(*A, *B)) {
                // Shape::resolveCollision(*A, *B);
                atreus::Event *event = new atreus::Event();
                event->type = atreus::Event::EventType::Collision;
                atreus::Event::CollisionEvent data;
                data.A               = A;
                data.B               = B;
                data.n               = Shape::calculateNormal(*A, *B, data.penetration);
                data.contact         = sf::Vector2f(3, 3);
                data.done            = false;
                event->collisionData = data;
                atreus::EventManager::pushEvent(event);
            }
        }
        if (asset->canBeRemoved()) {
            delete asset;
            itAsset = assets.erase(itAsset);
            --itAsset;
        }
    }

    extra_update(deltatime);
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (std::list<Asset *>::const_iterator itAsset = assets.begin(); itAsset != assets.end(); ++itAsset) {
        (*itAsset)->draw(target, states);
    }

    extra_draw(target, states);
}
