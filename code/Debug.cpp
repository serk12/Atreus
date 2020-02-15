#include "./Debug.h"

namespace atreus::Debug {
void print(const sf::Vector2f& v) {
    std::cout << "x: " << v.x << "; y: " << v.y << std::endl;
}

void print(const std::string& text) {
    std::cout << text << std::endl;
}
}
