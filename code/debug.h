#ifndef DEBUG_HH
#define DEBUG_HH

#include <iostream>

namespace debug {
void print(const sf::Vector2f& v) {
    std::cout << "x: " << v.x << "; y: " << v.y << std::endl;
}

void print(const std::string& text) {
    std::cout << text << std::endl;
}
}

#endif // DEBUG_HH
