#include "../header/Engine.h"

Engine::Engine() {}
Engine::~Engine()
{
    delete current_screen;
}

void Engine::start()
{
    window.create(sf::VideoMode(W_WIDTH, W_HEIGHT), APP_NAME);
    current_screen = new Screen();

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

        default:
            break;
        }
    }

    if (current_screen != NULL)
    {
        current_screen->event(event);
    }
}

void Engine::update_()
{
    sf::Time deltatime = clock.restart();
    if (current_screen != NULL)
    {
        current_screen->update(deltatime);
    }
}

void Engine::draw_()
{
    if (not window.isOpen()) return;

    window.clear(sf::Color::Black);

    if (current_screen != NULL)
    {
        window.draw(*current_screen);
    }

    window.display();
}
