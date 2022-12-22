#include "Torus.h"

Torus::Torus() : Shape3D() {

}

Torus::Torus(const Point3i& pos, const std::vector<int>& sides) 
: Shape3D(pos, sides) {

}

Torus::Torus(const Torus& another) 
: Shape3D(another) {

}


void Torus::render() 
{

}

void Torus::setMotion(void) 
{

}
