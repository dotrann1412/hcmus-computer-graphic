#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Shape.h"

class Triangle: public Shape
{
public:
	Triangle(const Point& rect_start, const Point& rect_end);
	Triangle(const Triangle& );
	void render();
	bool contain(const Point&);
};

#endif // __TRIANGLE_H__