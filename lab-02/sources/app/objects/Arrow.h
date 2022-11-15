#ifndef __ARROW_H__
#define __ARROW_H__

#include "Shape.h"

class Arrow: public Shape
{
public:
	Arrow(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Arrow(const Arrow& another);

	void render() const;
	bool contain(const Point& );
	void setBoundary(const Point&, const Point&);
	void unbound();
};

#endif // __ARROW_H__