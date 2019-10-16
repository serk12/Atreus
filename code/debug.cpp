#include <SFML/Graphics.hpp>
#include "./debug.h"

void debug::print(const sf::Vector2f& v) {
    std::cout << "x: " << v.x << "; y: " << v.y << std::endl;
}

void debug::print(const std::string& text) {
    std::cout << text << std::endl;
}
