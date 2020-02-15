#include "./Math.h"

namespace atreus::Math {
sf::Vector3f cross(const sf::Vector3f& A, const sf::Vector3f& B)
{
    return sf::Vector3f(A.y * B.z - A.z * B.y,
                        A.x * B.z - A.z * B.x,
                        A.x * B.y - A.y * B.x);
}

sf::Vector2f tangent(const sf::Vector2f& n, const sf::Vector2f& rv)
{
    float s = n.x * rv.y - n.y * rv.x;
    sf::Vector2f t(-s *n.y, s *n.x);
    float size = sqrt(t.x * t.x + t.y * t.y);
    if (size > 0.0f) return t / size;
    else return t;
}

float degreeToRad(float degree)
{
    return degree * PI / 180.0f;
}

float radToDegree(float rad)
{
    return rad * 180.0f / PI;
}
}
