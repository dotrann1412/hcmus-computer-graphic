#ifndef __HEXAGON_H__
#define __HEXAGON_H__

#include "Shape.h"

class Hexagon: public Shape
{
public:
	Hexagon(const Point& rect_Hexagont, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Hexagon(const Hexagon& another);

	void render() const;
	bool contain(const Point& );
	void setBoundary(const Point&, const Point&);
	void unbound();
};

#endif // __HEXAGON_H__