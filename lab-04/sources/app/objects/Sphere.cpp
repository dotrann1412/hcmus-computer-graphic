#include "Sphere.h"

const int Sphere::SECTOR_COUNT = 32;
const int Sphere::STACK_COUNT = 32;

Sphere::Sphere() : Shape3D() {

}

Sphere::Sphere(const Point3i& pos, const std::vector<int>& sides, const int& texture) 
: Shape3D(pos, sides, texture) {
	int m = min(xSide, min(ySide, zSide));
}

Sphere::Sphere(const Sphere& another) 
: Shape3D(another) {

}

Sphere::~Sphere() {

}

#include <iostream>

void Sphere::render() 
{
	Shape3D::render();
	glLoadIdentity();

	Point3i pts = center();
	glTranslatef(pts.x(), pts.y(), pts.z());
	
	float xy;

	float radius = 0.5 * min(xSide, min(ySide, zSide));

	static float sectorStep = 2.0 * PI / Sphere::SECTOR_COUNT;
	static float stackStep = PI / Sphere::STACK_COUNT;
	
	float sectorAngle, stackAngle;
	
	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	
	auto process = [&] (int ii, int jj) {
		stackAngle = PI / 2 - ii * stackStep;
		xy = radius * cosf(stackAngle);
		sectorAngle = jj * sectorStep;
		return setPixel(xy * cosf(sectorAngle), xy * sinf(sectorAngle), radius * sinf(stackAngle));
	};

	Point3i p;
	for (int i = 0; i < STACK_COUNT; ++i) {
		for (int j = 0; j < SECTOR_COUNT; ++j) {

			glTexCoord2f(1.0 * i / STACK_COUNT, 1.0 * j / SECTOR_COUNT);
			process(i, j);

			glTexCoord2f(1.0 * i / STACK_COUNT, 1.0 * (j + 1) / SECTOR_COUNT);
			process(i, (j + 1) % SECTOR_COUNT);

			glTexCoord2f(1.0 * (i + 1) / STACK_COUNT, 1.0 * (j + 1) / SECTOR_COUNT);
			process((i + 1) % STACK_COUNT, (j + 1) % SECTOR_COUNT);

			glTexCoord2f(1.0 * (i + 1) / STACK_COUNT, 1.0 * j / SECTOR_COUNT);
			process((i + 1) % STACK_COUNT, j);
		}
	}

	glEnd();
}

void Sphere::setMotion(void) 
{

}