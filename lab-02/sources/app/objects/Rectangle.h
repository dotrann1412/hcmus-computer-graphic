#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Shape.h"

class Rectangle: public Shape
{
public:
	Rectangle(const Point& rect_start, const Point& rect_end);
	Rectangle(const Rectangle& );
	~Rectangle() {};
	virtual void render(bool fill, std::function<void(const int&, const int&, const Pixel&)>);
	virtual bool contain(const Point&);
};

#endif // __RECTANGLE_H__