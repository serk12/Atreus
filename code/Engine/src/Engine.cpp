#include "../header/Engine.h"

int windowCoordx, windowCoordy;

Engine::Engine() {}
Engine::~Engine()
{
    delete currentScreen;
}

void Engine::start()
{
    window.create(sf::VideoMode(W_WIDTH, W_HEIGHT), APP_NAME);
    currentScreen = new Screen();

    while (window.isOpen())
    {
        event_();
        update_();
        draw_();
    }
}

void Engine::event_()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        windowCoordx = window.getPosition().x + correctWindowCoordx;
        windowCoordy = window.getPosition().y + correctWindowCoordy;

        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            break;

        case sf::Event::Resized:
            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            break;

        default:
            break;
        }

        if (currentScreen != NULL)
        {
            currentScreen->event(event);
        }
    }
}

void Engine::update_()
{
    sf::Time deltatime = clock.restart();
    if (currentScreen != NULL)
    {
        currentScreen->update(deltatime);
    }
}

void Engine::draw_()
{
    if (not window.isOpen()) return;

    window.clear(sf::Color::Black);

    if (currentScreen != NULL)
    {
        window.draw(*currentScreen);
    }

    window.display();
}
