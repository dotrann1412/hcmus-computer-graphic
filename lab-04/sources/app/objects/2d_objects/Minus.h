#ifndef __MINUS_H__
#define __MINUS_H__

#include "Shape2D.h"

class Minus: public Shape2D
{
public:
	Minus(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Minus(const Minus& another);

	void render() const;
	bool contain(const Point& );
	void setBoundary(const Point&, const Point&);
	void unbound();
};

#endif // __MINUS_H__