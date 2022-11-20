#ifndef __PENTAGON_H__
#define __PENTAGON_H__

#include "Shape.h"

class Pentagon: public Shape
{
public:
	Pentagon(const Point& rect_Pentagont, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	Pentagon(const Pentagon& another);

	void render() const;
	bool contain(const Point& );
	void setBoundary(const Point&, const Point&);
	void unbound();
};

#endif // __PENTAGON_H__