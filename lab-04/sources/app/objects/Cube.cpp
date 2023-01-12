#include "Cube.h"

Cube::Cube() 
: Shape3D() {

}

Cube::Cube(const Point3i& pos, const std::vector<int>& sides, const int& texture)
: Shape3D(pos, sides, texture) {

}

Cube::Cube(const Cube& another) 
: Shape3D(another) {

}

void Cube::render() 
{
	Shape3D::render();
	glLoadIdentity();

	Point3i pts = center();
	glTranslatef(mPos.x(), mPos.y(), mPos.z());

	static std::vector<std::vector<float>> texcoor = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f }
	};

	int cur = 0;

	std::vector<std::vector<int>> vertices = {
		{0, 0, 0},
		{xSide, 0, 0},
		{xSide, ySide, 0},
		{0, ySide, 0},
		
		{0, 0, zSide},
		{xSide, 0, zSide},
		{xSide, ySide, zSide},
		{0, ySide, zSide},

		{0, 0, 0},
		{0, ySide, 0},
		{0, ySide, zSide},
		{0, 0, zSide},

		{0, 0, 0},
		{xSide, 0, 0},
		{xSide, 0, zSide},
		{0, 0, zSide},

		{xSide, 0, 0},
		{xSide, ySide, 0},
		{xSide, ySide, zSide},
		{xSide, 0, zSide},

		{0, ySide, 0},
		{xSide, ySide, 0},
		{xSide, ySide, zSide},
		{0, ySide, zSide},

		{0, 0, zSide},
		{xSide, 0, zSide},
		{xSide, ySide, zSide},
		{0, ySide, zSide}
	};

	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	for (auto x: vertices) {
		glTexCoord2f(texcoor[cur][0], texcoor[cur][1]); cur = (cur + 1) % texcoor.size();
		setPixel(x[0], x[1], x[2]);
	}

	glEnd();

	//return;

	//// required attention

	//// bottom side
	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(0, 0, 0);
	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(xSide, 0, 0);
	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(xSide, ySide, 0);
	//glTexCoord2f(texcoor[cur][0], texcoor[cur][1]); cur = 0;
 //	setPixel(0, ySide, 0);

	//// left side
	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(0, 0, 0);
	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(0, ySide, 0);
	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(0, ySide, zSide);
	//glTexCoord2f(texcoor[cur][0], texcoor[cur][1]); cur = 0;
	//setPixel(0, 0, zSide);

	//// front side
	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(0, 0, 0);

	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(xSide, 0, 0);

	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(xSide, 0, zSide);

	//glTexCoord2f(texcoor[cur][0], texcoor[cur++][1]);
	//setPixel(0, 0, zSide);

	//// right side
	//glColor3ub(255, 0, 0);
	//setPixel(xSide, 0, 0);
	//setPixel(xSide, ySide, 0);
	//setPixel(xSide, ySide, zSide);
	//setPixel(xSide, 0, zSide);

	//// back side
	//glColor3ub(0, 255, 0);
	//setPixel(0, ySide, 0);
	//setPixel(xSide, ySide, 0);
	//setPixel(xSide, ySide, zSide);
	//setPixel(0, ySide, zSide);

	//// top side
	//glColor3ub(0, 0, 255);
	//setPixel(0, 0, zSide);
	//setPixel(xSide, 0, zSide);
	//setPixel(xSide, ySide, zSide);
	//setPixel(0, ySide, zSide);

	//glEnd();

	//glTranslatef(-mPos.x(), -mPos.y(), -mPos.z());
}

void Cube::setMotion(void) 
{

}
