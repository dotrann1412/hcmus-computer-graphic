#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Elipse.h"

class Circle: public Elipse
{
public:
	Circle(const Point& rect_start, const Point& rect_end);
	Circle(const Circle&);

	~Circle() {};

	void render();
	bool contain(const Point& );
};

#endif // __CIRCLE_H__