#ifndef __TIMES_H__
#define __TIMES_H__

#include "Shape2D.h"

class Times: public Shape2D
{
public:
	Times(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Times(const Times& another);

	void render() const;
	bool contain(const Point& );
	void setBoundary(const Point&, const Point&);
	void unbound();
};

#endif // __TIMES_H__