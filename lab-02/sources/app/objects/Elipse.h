#ifndef __ELIPSE_H__
#define __ELIPSE_H__

#include "Shape.h"

class Elipse: public Shape
{
public:
	Elipse(const Point& rect_start, const Point& rect_end,  
		const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE
	);
	
	Elipse(const Elipse&);
	
	virtual ~Elipse();

	virtual void render() const;
	virtual bool contain(const Point&);
	virtual void unbound();
	virtual void setBoundary(const Point& first, const Point& second);

protected:
	Point m_center;
	float m_a, m_b;
};

#endif // __ELIPSE_H__