#ifndef ENGINECONF_HH
#define ENGINECONF_HH
// default values
#define W_WIDTH 500
#define W_HEIGHT 500
#define FPS 120
#define APP_NAME "ATREUS"
// 'fix' for the inaccuracy for the mouse coords
#define correctWindowCoordx -8
#define correctWindowCoordy -38

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class EngineConf {
protected:
    static void setWindowCoords(int x, int y);
    static void setWindowSize(int x, int y);

    // window width and height size
    static int windowWidth, windowHeight;
    // window position coords
    // relativeMouseCoords = mouseCords - windowCoord
    static int windowCoordx, windowCoordy;
    static float fps, dt;

public:
    static float getFPS();
    static float getDt();

    static sf::Vector2f getWindowSize();
    static sf::Vector2f getWindowCoords();
};

#endif // ifndef ENGINECONF_HH
