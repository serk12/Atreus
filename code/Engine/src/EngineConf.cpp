#include "../header/EngineConf.h"

float EngineConf::fps = FPS;
float EngineConf::dt  = 1 / fps;

int EngineConf::windowCoordx;
int EngineConf::windowCoordy;
int EngineConf::windowWidth  = W_WIDTH;
int EngineConf::windowHeight = W_HEIGHT;


void EngineConf::setWindowCoords(int x, int y)
{
    windowCoordx = x;
    windowCoordy = y;
}

void EngineConf::setWindowSize(int width, int height)
{
    windowWidth  = width;
    windowHeight = height;
}

float EngineConf::getFPS()
{
    return EngineConf::fps;
}

float EngineConf::getDt()
{
    return EngineConf::dt;
}

sf::Vector2f EngineConf::getWindowSize()
{
    return sf::Vector2f(windowWidth, windowHeight);
}

sf::Vector2f EngineConf::getWindowCoords()
{
    return sf::Vector2f(windowCoordx, windowCoordy);
}
