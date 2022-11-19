#ifndef __DIVIDE_H__
#define __DIVIDE_H__

#include "Shape.h"

class Divide: public Shape
{
public:
	Divide(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Divide(const Divide& another);

	void render() const;
	bool contain(const Point& );
	void setBoundary(const Point&, const Point&);
	void unbound();
};

#endif // __DIVIDE_H__