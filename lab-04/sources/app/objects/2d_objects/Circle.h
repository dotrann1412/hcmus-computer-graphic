#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Elipse.h"

class Circle: public Elipse
{
public:
	Circle(const Point& rect_start, const Point& rect_end,  const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);
	
	Circle(const Circle&);

	~Circle() {};

	void render() const;
	bool contain(const Point& );
	void unbound();
	void setBoundary(const Point&, const Point& );
};

#endif // __CIRCLE_H__