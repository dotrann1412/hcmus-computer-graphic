#include "Hyperpoloid.h"

Hyperpoloid::Hyperpoloid() : Shape3D() {

}

Hyperpoloid::Hyperpoloid(const Point3i& pos, const std::vector<int>& sides) 
: Shape3D(pos, sides) {

}

Hyperpoloid::Hyperpoloid(const Hyperpoloid& another) 
: Shape3D(another) {

}


void Hyperpoloid::render() 
{

}

void Hyperpoloid::setMotion(void) 
{

}
