#ifndef UTILS_HH
#define UTILS_HH

// default values
#define W_WIDTH 500
#define W_HEIGHT 500
#define FPS 120
#define APP_NAME "ATREUS"

//'fix' for the inaccuracy for the mouse coords
#define correctWindowCoordx -8
#define correctWindowCoordy -38

//window width and height size
extern int windowWidth, windowHeight;

//window position coords
//relativeMouseCoords = mouseCords - windowCoord
extern int windowCoordx, windowCoordy;

#endif //UTILS_HH
