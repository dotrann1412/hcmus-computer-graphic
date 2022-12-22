#include "Cone.h"

Cone::Cone() : Shape3D() {

}

Cone::Cone(const Point3i& pos, const std::vector<int>& sides)
: Shape3D(pos, sides) {

}

Cone::Cone(const Cone& another) 
: Shape3D(another) {

}


void Cone::render() 
{

}

void Cone::setMotion(void) 
{

}
