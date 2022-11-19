#include "Rectangle.h"


Rectangle::Rectangle(const Point& rect_start, const Point& rect_end, const Color& boundary_color, const Color& fill_color) 
	: Shape(rect_start, rect_end, boundary_color, fill_color) {

}

Rectangle::Rectangle(const Rectangle& another) 
	: Shape(another) {

}

void Rectangle::render() const
{
	Point topLeft 	= {m_bottomLeft.x(), m_topRight.y()}, 
		bottomRight = {m_topRight.x(), m_bottomLeft.y()};

	bresenham(m_bottomLeft, topLeft);
	bresenham(topLeft, m_topRight);
	bresenham(m_topRight, bottomRight);
	bresenham(bottomRight, m_bottomLeft);
	
	boundary_fill();
}

void Rectangle::unbound() {
	Point topLeft 	= {m_bottomLeft.x(), m_topRight.y()}, 
		bottomRight = {m_topRight.x(), m_bottomLeft.y()};

	bresenham_rev(m_bottomLeft, topLeft);
	bresenham_rev(topLeft, m_topRight);
	bresenham_rev(m_topRight, bottomRight);
	bresenham_rev(bottomRight, m_bottomLeft);
}

bool Rectangle::contain(const Point& point) {
	return Shape::contain(point);
}