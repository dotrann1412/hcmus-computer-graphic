#ifndef __SHAPE3D_H__
#define __SHAPE3D_H__

#include "Point3i.h"
#include <gl/glut.h>
#include <vector>

#include <algorithm>
using std::min, std::max, std::acos;

const float PI = acos(-1);

class Shape3D
{
public:
	Shape3D();
	Shape3D(const Point3i& pos, const std::vector<int>& sides);
	Shape3D(const Shape3D& another);

	Point3i center();
	virtual void rotate(float, float, float);
	
	virtual ~Shape3D();

public:
	virtual void render() {};
	virtual void setMotion(void) {};

protected:
	void setPixel(float, float, float);

protected:
	Point3i mPos;
	int xSide, ySide, zSide;
	std::vector<std::vector<float>> mRotation;	
};

#endif