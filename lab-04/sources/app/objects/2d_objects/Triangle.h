#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Shape2D.h"

class Triangle: public Shape2D
{
public:
	Triangle(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Triangle(const Triangle& );
	void render() const;
	bool contain(const Point&);
	void unbound();
};

#endif // __TRIANGLE_H__