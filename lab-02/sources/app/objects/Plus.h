#ifndef __PLUS_H__
#define __PLUS_H__

#include "Shape.h"

class Plus: public Shape
{
public:
	Plus(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Plus(const Plus& another);

	void render() const;
	bool contain(const Point& );
	void setBoundary(const Point&, const Point&);
	void unbound();
};

#endif // __PLUS_H__