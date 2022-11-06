#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Point.h"
#include "Color.h"

#ifdef __linux__ 
#include <GL/glut.h>
#else
#include <gl/glut.h>
#endif

class Shape
{
public:
	Shape(const Point& rect_start, const Point& rect_end);
	Shape(const Shape& another);

	virtual void render() = 0;
	virtual bool contain(const Point& point);
	virtual ~Shape();
	virtual void fill(const Color&);


protected: // save the boundary
	Point m_bottomLeft;
	Point m_topRight;
};

#endif // __SHAPE_H__