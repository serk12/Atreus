#include "../header/Shape.h"

/*--------------------------------------------------*/
/*                      Shape                       */
/*--------------------------------------------------*/

//  Rock       Density : 0.6  Restitution : 0.1
//  Wood       Density : 0.3  Restitution : 0.2
//  Metal      Density : 1.2  Restitution : 0.05
//  BouncyBall Density : 0.3  Restitution : 0.8
//  SuperBall  Density : 0.3  Restitution : 0.95
//  Pillow     Density : 0.1  Restitution : 0.2
//  Static     Density : 0.0  Restitution : 0.4

void Shape::event(sf::Event event)
{}

void Shape::update(const float deltatime)
{}

// Broad Detection using AABBx to have a cheap and quick solution
bool Shape::broadDetection(const Shape& A, const Shape& B)
{
    // get IntRect and make AAGG vs AABB
}

bool Shape::narrowDetection(const Shape& A, const Shape& B)
{}
