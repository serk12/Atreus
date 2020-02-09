#ifndef MATH_HH
#define MATH_HH

#include <SFML/Graphics.hpp>
#include <random>
#include "./debug.h"
namespace atreus {
namespace Math {
sf::Vector3f cross(const sf::Vector3f& A, const sf::Vector3f& B);
sf::Vector2f tangent(const sf::Vector2f& n, const sf::Vector2f& rv);
}
}

#endif // ifndef MATH_HH
