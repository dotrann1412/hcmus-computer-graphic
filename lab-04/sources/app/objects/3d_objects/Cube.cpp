#include "Cube.h"

Cube::Cube() 
: Shape3D() {

}

Cube::Cube(const Point3i& pos, const std::vector<int>& sides)
: Shape3D(pos, sides) {

}

Cube::Cube(const Cube& another) 
: Shape3D(another) {

}

void Cube::render() 
{
	glLoadIdentity();
	glTranslatef(mPos.x(), mPos.y(), mPos.z());
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 255);
	// required attention

	// bottom side
	setPixel(0, 0, 0);
	setPixel(xSide, 0, 0);
	setPixel(xSide, ySide, 0);
	setPixel(0, ySide, 0);

	// left side
	glColor3ub(0, 255, 255);
	setPixel(0, 0, 0);
	setPixel(0, ySide, 0);
	setPixel(0, ySide, zSide);
	setPixel(0, 0, zSide);

	// front side
	glColor3ub(255, 255, 0);
	setPixel(0, 0, 0);
	setPixel(xSide, 0, 0);
	setPixel(xSide, 0, zSide);
	setPixel(0, 0, zSide);

	// right side
	glColor3ub(255, 0, 0);
	setPixel(xSide, 0, 0);
	setPixel(xSide, ySide, 0);
	setPixel(xSide, ySide, zSide);
	setPixel(xSide, 0, zSide);

	// back side
	glColor3ub(0, 255, 0);
	setPixel(0, ySide, 0);
	setPixel(xSide, ySide, 0);
	setPixel(xSide, ySide, zSide);
	setPixel(0, ySide, zSide);

	// top side
	glColor3ub(0, 0, 255);
	setPixel(0, 0, zSide);
	setPixel(xSide, 0, zSide);
	setPixel(xSide, ySide, zSide);
	setPixel(0, ySide, zSide);

	glEnd();

	glTranslatef(-mPos.x(), -mPos.y(), -mPos.z());
}

void Cube::setMotion(void) 
{

}
