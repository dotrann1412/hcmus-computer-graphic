#include "Torus.h"

Torus::Torus() : Shape3D() {

}

Torus::Torus(const Point3i& pos, const std::vector<int>& sides, const int& texture) 
: Shape3D(pos, sides, texture) {

}

Torus::Torus(const Torus& another) 
: Shape3D(another) {

}

#include <iostream>

void Torus::render() 
{
	Shape3D::render();
	glLoadIdentity();

	glTranslatef(mPos.x(), mPos.y(), mPos.z());

	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	float outer_radius = std::min(xSide, std::min(ySide, zSide)) / 2;
	float inner_radius = outer_radius / 2;

	float dPI = 2.0 * KS_PI;

	auto process = [&] (int ii, int jj) {
		float theta = dPI * jj / KS_NUMT;
		float phi = dPI * ii / KS_NUMC;

		float x = ((outer_radius + inner_radius * cos(theta)) * cos(phi)) + 1.0 * xSide / 2;
		float y = ((outer_radius + inner_radius * cos(theta)) * sin(phi)) + 1.0 * ySide / 2;
		float z = (inner_radius * sin(theta)) + 1.0 * zSide / 2;

		return setPixel(x, y, z);
	};
	
	for (int i = 0; i < KS_NUMC; i++) {
		for (int j = 0; j < KS_NUMT; j++) {
			
			glTexCoord2f(1.0 * i / KS_NUMC, 1.0 * j / KS_NUMT);
			process(i, j);

			glTexCoord2f(1.0 * i / KS_NUMC, 1.0 * (j + 1) / KS_NUMT);
			process(i, j + 1);

			glTexCoord2f(1.0 * (i + 1) / KS_NUMC, 1.0 * (j + 1) / KS_NUMT);
			process(i + 1, j + 1);

			glTexCoord2f(1.0 * (i + 1) / KS_NUMC, 1.0 * j / KS_NUMT);
			process(i + 1, j);
		}
	} 

	glEnd();

}

void Torus::setMotion(void) 
{

}

const int Torus::KS_NUMC = 32;
const int Torus::KS_NUMT = 32;