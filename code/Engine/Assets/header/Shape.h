#ifndef SHAPE_HH
#define SHAPE_HH

#include "Asset.h"
#include <random>

struct MassData
{
    float mass, inv_mass;
    float inertia, inverse_inertia;
};

struct Material
{
    float density, restitution;
};

class Shape : public Asset {
private:
    float gravityScale;
    Material material;
    MassData mass_data;
    sf::Vector2f velocity;

    sf::Vector2f potentialForce;
    sf::Vector2f externalForce;

public:
    void event(sf::Event event) final;
    void update(const float deltatime) final;

    virtual const sf::IntRect getPossitionAndSizeRect() {};

    static bool broadDetection(const Shape& A, const Shape& B);
    static bool narrowDetection(const Shape& A, const Shape& B);
};

#endif // ifndef SHAPE_HH
