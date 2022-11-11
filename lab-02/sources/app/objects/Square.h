#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Rectangle.h"

class Square: public Rectangle
{
public:
	Square(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Square(const Square& another);
	void setBoundary(const Point& first, const Point& last);
};

#endif // __SQUARE_H__