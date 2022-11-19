#include "Triangle.h"
#include "Line.h"
#include <vector>

#include "./helpers.h"

Triangle::Triangle(const Point& rect_start, const Point& rect_end, const Color& boundary_color, const Color& fill_color) 
	: Shape(rect_start, rect_end, boundary_color, fill_color) {

}

Triangle::Triangle(const Triangle& another) 
	: Shape(another) {

}

void Triangle::render() const {
	Point top = {(m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y()};
	
	bresenham(m_bottomLeft, top);
	bresenham(top, {m_topRight.x(), m_bottomLeft.y()});
	bresenham(m_bottomLeft, {m_topRight.x(), m_bottomLeft.y()});

	boundary_fill();
}

void Triangle::unbound() {
	Point top = {(m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y()};
	bresenham_rev(m_bottomLeft, top);
	bresenham_rev(top, {m_topRight.x(), m_bottomLeft.y()});
	bresenham_rev(m_bottomLeft, {m_topRight.x(), m_bottomLeft.y()});
}

bool Triangle::contain(const Point& pts) {
	if (!Shape::contain(pts))
		return false;
	Point top = {(m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y()};
	std::vector<Line> boundary = {
		{m_bottomLeft, top},
		{top, {m_topRight.x(), m_bottomLeft.y()}},
		{m_bottomLeft, {m_topRight.x(), m_bottomLeft.y()}}
	};
	return inside(pts, boundary);
}