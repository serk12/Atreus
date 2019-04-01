#ifndef SHAPECONF_HH
#define SHAPECONF_HH


struct MassData
{
    float mass, inv_mass;
    float inertia, inverse_inertia;
};

struct Material
{
    float density, restitution;
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

#endif
