#include "../header/Engine.h"

const float Engine::timeClamp = 0.2f;

Engine::Engine() {}
Engine::~Engine()
{
    delete currentScreen;
    window.close();
}

void Engine::start()
{
    sf::Vector2f size = EngineConf::getWindowSize();
    window.create(sf::VideoMode(size.x, size.y), APP_NAME);
    window.setFramerateLimit(FPS);
    accumulator   = 0;
    currentScreen = new Screen();

    while (window.isOpen()) {
        event_();
        update_();
        draw_();
    }
}

void Engine::event_()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        this->setWindowCoords(window.getPosition().y, window.getPosition().x);
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            break;

        case sf::Event::Resized:
            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            this->setWindowSize(event.size.width, event.size.height);
            break;

        default:
            break;
        }

        if (currentScreen != NULL) {
            currentScreen->event(event);
        }
    }

    atreus::Event *eventA = NULL;
    while (atreus::EventManager::pollEvent(eventA)) {
        if (currentScreen != NULL) {
            currentScreen->event((*eventA));
        }
    }
}

void Engine::update_()
{
    accumulator += clock.restart().asSeconds();
    float dt = EngineConf::getDt();
    if (accumulator > timeClamp) accumulator = timeClamp;
    while (accumulator > dt) {
        currentScreen->update(dt);
        accumulator -= dt;
    }
    /*
       const float alpha = accumulator / dt;
       // renderGame(alpha)
        -> interpolate  transform = previous * alpha + current * (1.0 - alpha)
     */
}

void Engine::draw_()
{
    if (not window.isOpen()) return;

    window.clear(sf::Color::Black);

    if (currentScreen != NULL) {
        window.draw(*currentScreen);
    }

    window.display();
}
