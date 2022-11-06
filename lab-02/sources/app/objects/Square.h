#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Rectangle.h"

class Square: public Rectangle
{
public:
	Square(const Point& rect_start, const Point& rect_end);
	Square(const Square& another);
};

#endif // __SQUARE_H__