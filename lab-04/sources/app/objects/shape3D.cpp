#include "Shape3D.h"

#include <iostream>
#include <math.h>
#include <cassert>

template<class T>
std::vector<std::vector<T>> operator * (const std::vector<std::vector<T>>& aa, const std::vector<std::vector<T>>& bb) {
    assert(aa[0].size() == bb.size());

    std::vector<std::vector<T>> res(aa.size(), std::vector<T>(bb[0].size(), 0));
    for (int i = 0; i < aa.size(); ++i) {
        for (int j = 0; j < bb.size(); ++j) {
            for (int k = 0; k < aa[i].size(); ++k) {
                res[i][j] += aa[i][k] * bb[k][j];
            }
        }
    }

    return res;
}

Shape3D::Shape3D(): mPos(0, 0, 0), xSide(1), ySide(1), zSide(1) {
    mRotation = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
    mTexture = 0;
}

Shape3D::Shape3D(const Point3i& pos, const std::vector<int>& sides, const int& texture)
: mPos(pos), mTexture(texture) {
	if (sides.size() != 3) std::cerr << "[ERROR] 3d shape should be created with starting position and exactly 3 sides. Found: " << sides.size() << '\n'; 
	else xSide = sides[0], ySide = sides[1], zSide = sides[2];
	mRotation = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

Shape3D::Shape3D(const Shape3D& shape) 
	: mPos(shape.mPos), xSide(shape.xSide), ySide(shape.ySide), zSide(shape.zSide), 
    mRotation(shape.mRotation), mTexture(shape.mTexture) {

}

Shape3D::~Shape3D() {}

Point3i Shape3D::center() {
	return { mPos.x() + 1.0f * xSide / 2, mPos.y() + 1.0f * ySide / 2, mPos.z() + 1.0f * zSide / 2 };
}

void Shape3D::render() {
    return;
    glLoadIdentity();

    Point3i pts = center();

    glTranslatef(
        pts.x(), pts.y(), pts.z()
    );

    // draw grid box
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);

    // x axis
    setPixel(0, 0, 0);
    setPixel(xSide, 0, 0);

    // y axis
    setPixel(0, 0, 0);
    setPixel(0, ySide, 0);

    // z axis
    setPixel(0, 0, 0);
    setPixel(0, 0, zSide);

    glEnd();
}

void Shape3D::setPixel(float x, float y, float z) {
    glVertex3f(
        x * mRotation[0][0] + y * mRotation[1][0] + z * mRotation[2][0] + mRotation[3][0],
        x * mRotation[0][1] + y * mRotation[1][1] + z * mRotation[2][1] + mRotation[3][1],
        x * mRotation[0][2] + y * mRotation[1][2] + z * mRotation[2][2] + mRotation[3][2]
    );
}

void Shape3D::rotate(float x, float y, float z) {
    float cosx = cos(x), sinx = sin(x);

    std::vector<std::vector<float>> xaxis = {
        {1, 0, 0, 0},
        {0, cosx, sinx, 0},
        {0, -sinx, cosx, 0},
        {0, 0, 0, 1}
    };

    float cosy = cos(y), siny = sin(y);

    std::vector<std::vector<float>> yaxis = {
        {cosy, 0, -siny, 0},
        {0, 1, 0, 0},
        {siny, 0, cosy, 0},
        {0, 0, 0, 1}
    };

    float cosz = cos(z), sinz = sin(z);

    std::vector<std::vector<float>> zaxis = {
        {cosz, sinz, 0, 0}, 
        {-sinz, cosz, 0, 0}, 
        {0, 0, 1, 0}, 
        {0, 0, 0, 1}
    };

    mRotation = mRotation * xaxis * yaxis * zaxis;
}

const double Shape3D::KS_PI = acos(-1);