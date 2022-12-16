#ifndef __STAR_H__
#define __STAR_H__

#include "Shape.h"

class Star: public Shape
{
public:
	Star(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Star(const Star& another);

	void render() const;
	bool contain(const Point& );
	void setBoundary(const Point&, const Point&);
	void unbound();
};

#endif // __STAR_H__