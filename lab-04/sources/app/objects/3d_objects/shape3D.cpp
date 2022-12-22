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
}

Shape3D::Shape3D(const Point3i& pos, const std::vector<int>& sides)
: mPos(pos) {
	if (sides.size() != 3)
		std::cerr << "[ERROR] 3d shape should be created with starting position and exactly 3 sides. Found: " << sides.size() << '\n'; 
	else xSide = sides[0], ySide = sides[1], zSide = sides[2];
	mRotation = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

Shape3D::Shape3D(const Shape3D& shape) 
	: mPos(shape.mPos), xSide(shape.xSide), ySide(shape.ySide), zSide(shape.zSide), mRotation(shape.mRotation) {

}

Shape3D::~Shape3D() {}

Point3i Shape3D::center() {
	return { mPos.x() + xSide / 2, mPos.y() + ySide / 2, mPos.z() + zSide };
}

void Shape3D::setPixel(float x, float y, float z) {
    glVertex3f(
        x * mRotation[0][0] + y * mRotation[1][0] + z * mRotation[2][0] + mRotation[3][0],
        x * mRotation[0][1] + y * mRotation[1][1] + z * mRotation[2][1] + mRotation[3][1],
        x * mRotation[0][2] + y * mRotation[1][2] + z * mRotation[2][2] + mRotation[3][2]
    );
}

void Shape3D::rotate(float x, float y, float z) {
    std::vector<std::vector<float>> xaxis = {
        {1, 0, 0, 0},
        {0, cos(x), sin(x), 0},
        {0, -sin(x), cos(x), 0},
        {0, 0, 0, 1}
    };

    std::vector<std::vector<float>> yaxis = {
        {cos(y), 0, -sin(y), 0},
        {0, 1, 0, 0},
        {sin(y), 0, cos(y), 0},
        {0, 0, 0, 1}
    };

    std::vector<std::vector<float>> zaxis = {
        {cos(z), sin(z), 0, 0}, 
        {-sin(z), cos(z), 0, 0}, 
        {0, 0, 1, 0}, 
        {0, 0, 0, 1}
    };

    mRotation = mRotation * xaxis;
    mRotation = mRotation * yaxis;
    mRotation = mRotation * zaxis;
}