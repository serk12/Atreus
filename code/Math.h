#ifndef MATH_HH
#define MATH_HH

#include <SFML/Graphics.hpp>
#include <random>
#include "./Debug.h"
namespace atreus {
namespace Math {
const float PI = 3.141516;

sf::Vector3f cross(const sf::Vector3f& A, const sf::Vector3f& B);
sf::Vector2f tangent(const sf::Vector2f& n, const sf::Vector2f& rv);

float degreeToRad(float angle);
float radToDegree(float rad);
}
}

#endif // ifndef MATH_HH
