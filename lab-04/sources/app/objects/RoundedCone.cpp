#include "RoundedCone.h"

RoundedCone::RoundedCone() : Shape3D() {

}

RoundedCone::RoundedCone(const Point3i& pos, const std::vector<int>& sides, const int& texture)
: Shape3D(pos, sides, texture) {

}

RoundedCone::RoundedCone(const RoundedCone& another) 
: Shape3D(another) {

}


void RoundedCone::render() 
{
	Shape3D::render();
	glLoadIdentity();

	Point3i pts = center();
	
	glTranslatef (
		pts.x(), pts.y(), pts.z()
	);

	glBegin(GL_QUADS);
	std::vector<std::vector<uint8_t>> colors = {
		{100, 100, 100},
		{150, 150, 150},
		{200, 200, 200},
	};

	int cur = 0;
	int radius = std::min(zSide, ySide) / 2;
	int height = zSide;

    float x, y, z, t, s;
    // draw a cone shape with f(theta, h) = (h.cos(theta), h.sin(theta), h)

    for (int h = KS_NUMC; h > KS_NUMC / 2; --h) {
        for (int i = 0; i <= KS_NUMT; ++i) {
            float theta1 = 2.0 * KS_PI * i / (KS_NUMT - 1);
            float theta2 = 2.0 * KS_PI * (i + 1) / (KS_NUMT - 1);
            
            float h1 = 1.0 * h / KS_NUMC;
            float h2 = 1.0 * (h - 1) / KS_NUMC;

            x = h1 * radius * cos(theta1);
            y = h1 * radius * sin(theta1);
            z = h1 * height - 1.0 * zSide / 2;

            glColor3ub(colors[cur][0], colors[cur][1], colors[cur][2]);
            setPixel(x, y, z);

            x = h1 * radius * cos(theta2);
            y = h1 * radius * sin(theta2);
            z = h1 * height - 1.0 * zSide / 2;

            glColor3ub(colors[cur][0], colors[cur][1], colors[cur][2]);
            setPixel(x, y, z);

            x = h2 * radius * cos(theta2);
            y = h2 * radius * sin(theta2);
            z = h2 * height - 1.0 * zSide / 2;

            glColor3ub(colors[cur][0], colors[cur][1], colors[cur][2]);
            setPixel(x, y, z);

            x = h2 * radius * cos(theta1);
            y = h2 * radius * sin(theta1);
            z = h2 * height - 1.0 * zSide / 2;

            glColor3ub(colors[cur][0], colors[cur][1], colors[cur][2]);
            setPixel(x, y, z);
        }
    }

    glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(colors[cur][0], colors[cur][1], colors[cur][2]);

	for (int i = 0; i <= KS_NUMT; ++i) {
		float theta = 2.0 * KS_PI * i / (KS_NUMT - 1);

		x = radius * cos(theta);
		y = radius * sin(theta);
		z = 1.0 * height - 1.0 * zSide / 2;

		setPixel(x, y, z);
	}

	glEnd();
}

void RoundedCone::setMotion(void) 
{

}

const int RoundedCone::KS_NUMC = 32;
const int RoundedCone::KS_NUMT = 64;