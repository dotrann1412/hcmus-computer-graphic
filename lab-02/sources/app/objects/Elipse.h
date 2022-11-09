#ifndef __ELIPSE_H__
#define __ELIPSE_H__

#include "Shape.h"

class Elipse: public Shape
{
public:
	Elipse(const Point& rect_start, const Point& rect_end);
	Elipse(const Elipse&);
	
	virtual ~Elipse();
	virtual void render();
	virtual bool contain(const Point&);

protected:
	Point m_center;
	float m_a, m_b;
};

#endif // __ELIPSE_H__