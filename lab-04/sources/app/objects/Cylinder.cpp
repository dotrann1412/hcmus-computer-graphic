#include "Cylinder.h"

Cylinder::Cylinder() : Shape3D() {

}

Cylinder::Cylinder(const Point3i& pos, const std::vector<int>& sides, const int& texture) 
: Shape3D(pos, sides, texture) {

}

Cylinder::Cylinder(const Cylinder& another) 
: Shape3D(another) {

}

void Cylinder::render() 
{
    Shape3D::render();
    glLoadIdentity();

    Point3i pts = center();
    glTranslatef(mPos.x(), mPos.y(), mPos.z());

    
    float texX = 0, texY = 0;
    float stepX = 1.0 / 20;

    // draw a circle at the bottom
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 18) {
        float degInRad = KS_PI * i / 180;
        glTexCoord2f(1.0 * i / 360, 1.0 * i / 360);
        setPixel(cos(degInRad) * xSide / 2 + xSide / 2, sin(degInRad) * ySide / 2 + ySide / 2, 0);
    }
    glEnd();

    // draw a circle at the top
    texX = 0;
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i += 18, texX += stepX) {
        float degInRad = KS_PI * i / 180;
        glTexCoord2f(1.0 * i / 360, 1.0 * i / 360);
        setPixel(cos(degInRad) * xSide / 2 + xSide / 2, sin(degInRad) * ySide / 2 + ySide / 2, zSide);
    }
    glEnd();
    // draw the side
    glBegin(GL_QUAD_STRIP);
    texX = 0;
    for (int i = 0, state = 0; i <= 360; i += 18, ++state, texX += stepX) {
        float degInRad = 1.0 * i * KS_PI / 180;
        
        float x = cos(degInRad) * xSide / 2 + xSide / 2;
        float y = sin(degInRad) * ySide / 2 + ySide / 2;

        glTexCoord2f(1.0 * i / 360, 0); 
        setPixel(x, y, 0);
        glTexCoord2f(1.0 * i / 360, 1);
        setPixel(x, y, zSide);
    }
    glEnd();
}

void Cylinder::setMotion(void) 
{

}
