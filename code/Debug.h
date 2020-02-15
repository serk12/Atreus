#ifndef DEBUG_HH
#define DEBUG_HH

#include <iostream>
#include <SFML/Graphics.hpp>

namespace atreus {
namespace Debug {
void print(const sf::Vector2f& v);
void print(const std::string& text);
}
}

#endif // DEBUG_HH
