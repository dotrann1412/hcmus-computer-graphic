#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Point.h"
#include "Color.h"

#ifdef __linux__ 
#include <GL/glut.h>
#else
#include <gl/glut.h>
#endif

class Shape
{
public:
	Shape(const Point& rect_start, const Point& rect_end, const int& id);

	Shape(const Shape& another);

	virtual void render(bool fill, std::function<void(const int&, const int&, const Pixel&)>) = 0;
	
	virtual bool contain(const Point& point);
	
	virtual ~Shape();

	virtual Point center() const;

	virtual void boundary_fill(std::function<void(const int&, const int&, const Pixel&)>) const;

protected:
	void bresenham(
		const Point& first, 
		const Point& last, 
		const Color& color, 
		std::function<void(const int&, const int&, const Pixel&)>
	);

protected: // save the boundary
	Point m_bottomLeft;

	Point m_topRight;

	Color m_boundaryColor;

	Color m_fillColor;

	Color m_id;
};

#endif // __SHAPE_H__