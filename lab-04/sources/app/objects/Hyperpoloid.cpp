#include "Hyperpoloid.h"

Hyperpoloid::Hyperpoloid() : Shape3D() {

}

Hyperpoloid::Hyperpoloid(const Point3i& pos, const std::vector<int>& sides, const int& texture) 
: Shape3D(pos, sides, texture) {

}

Hyperpoloid::Hyperpoloid(const Hyperpoloid& another) 
: Shape3D(another) {

}


void Hyperpoloid::render() 
{
    Shape3D::render();
	glLoadIdentity();

	Point3i pts = center();
	
	glTranslatef (
		pts.x(), pts.y(), pts.z()
	);

	glBegin(GL_QUADS);
    glBindTexture(GL_TEXTURE_2D, mTexture);

	int cur = 0;
    float height = zSide / 2;

    // draw a hyperboloid x^2 + y^2 - z^2 = 1
    for (int i = 0; i < KS_NUMC; ++i) {
        for (int j = 0; j < KS_NUMT; ++j) {
            float u_normal = ((height * 2 * i / (KS_NUMC - 1)) - height) / KS_C;
            float v_normal = 2.0 * KS_PI * j / (KS_NUMT);

            float x = 1.0 * KS_A * sqrt(1 + u_normal * u_normal) * cos(v_normal);
            float y = 1.0 * KS_B * sqrt(1 + u_normal * u_normal) * sin(v_normal);
            float z = 1.0 * KS_C * u_normal * height / 2;

            glTexCoord2f(1.0 * i / KS_NUMC, 1.0 * j / KS_NUMT);
            setPixel(x, y, z);

            u_normal = ((height * 2 * i / (KS_NUMC - 1)) - height) / KS_C;
            v_normal = 2.0 * KS_PI * (j + 1) / (KS_NUMT);

            x = 1.0 * KS_A * sqrt(1 + u_normal * u_normal) * cos(v_normal);
            y = 1.0 * KS_B * sqrt(1 + u_normal * u_normal) * sin(v_normal);
            z = 1.0 * KS_C * u_normal * height / 2;

            glTexCoord2f(1.0 * i / KS_NUMC, 1.0 * (j + 1) / KS_NUMT);
            setPixel(x, y, z);

            u_normal = ((height * 2 * (i + 1) / (KS_NUMC - 1)) - height) / KS_C;
            v_normal = 2 * KS_PI * (j + 1) / (KS_NUMT);

            x = 1.0 * KS_A * sqrt(1 + u_normal * u_normal) * cos(v_normal);
            y = 1.0 * KS_B * sqrt(1 + u_normal * u_normal) * sin(v_normal);
            z = 1.0 * KS_C * u_normal * height / 2;

            glTexCoord2f(1.0 * (i + 1) / KS_NUMC, 1.0 * (j + 1) / KS_NUMT);
            setPixel(x, y, z);

            u_normal = ((height * 2 * (i + 1) / (KS_NUMC - 1)) - height) / KS_C;
            v_normal = 2.0 * KS_PI * j / (KS_NUMT);

            x = 1.0 * KS_A * sqrt(1 + u_normal * u_normal) * cos(v_normal);
            y = 1.0 * KS_B * sqrt(1 + u_normal * u_normal) * sin(v_normal);
            z = 1.0 * KS_C * u_normal * height / 2;

            glTexCoord2f(1.0 * (i + 1) / KS_NUMC, 1.0 * j / KS_NUMT);
            setPixel(x, y, z);
        }
    }

    glEnd();
}

void Hyperpoloid::setMotion(void) 
{

}

const int Hyperpoloid::KS_NUMT = 32;
const int Hyperpoloid::KS_NUMC = 32;
const float Hyperpoloid::KS_A = 1;
const float Hyperpoloid::KS_B = 1;
const float Hyperpoloid::KS_C = 1;
const float Hyperpoloid::KS_ANGLE = Shape3D::KS_PI / 3;
