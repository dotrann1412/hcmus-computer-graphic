#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Shape.h"

class Rectangle: public Shape
{
public:
	Rectangle(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Rectangle(const Rectangle& );
	~Rectangle() {};
	virtual void render() const;
	virtual bool contain(const Point&);
	virtual void unbound();
};

#endif // __RECTANGLE_H__