#ifndef SHAPECONF_HH
#define SHAPECONF_HH


struct MassData
{
    float mass, invMass;
    float inertia, inverseInertia;
};

struct Material
{
    float density, restitution, staticFriction, dynamicFriction;
};

class ShapeConf {
  public:
    static const Material Rock;
    static const Material Wood;
    static const Material Metal;
    static const Material BouncyBall;
    static const Material SuperBall;
    static const Material Pillow;
    static const Material Static;
};

#endif // ifndef SHAPECONF_HH
