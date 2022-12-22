#include "Cylinder.h"

Cylinder::Cylinder() : Shape3D() {

}

Cylinder::Cylinder(const Point3i& pos, const std::vector<int>& sides) 
: Shape3D(pos, sides) {

}

Cylinder::Cylinder(const Cylinder& another) 
: Shape3D(another) {

}


void Cylinder::render() 
{

}

void Cylinder::setMotion(void) 
{

}
