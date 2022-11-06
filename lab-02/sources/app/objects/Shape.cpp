#include "Shape.h"

#include "cmath"

Shape::Shape(const Point& rect_start, const Point& rect_end) {
	m_bottomLeft = {std::min(rect_start.x(), rect_end.x()), std::min(rect_start.y(), rect_end.y())};
	m_topRight = {std::max(rect_start.x(), rect_end.x()), std::max(rect_start.y(), rect_end.y())};
}

Shape::Shape(const Shape& another) {
	m_bottomLeft = another.m_bottomLeft;
	m_topRight = another.m_topRight;
}

Shape::~Shape() {
	// do nothing
}

bool Shape::contain(const Point& point) {
	return point.x() >= m_bottomLeft.x() && point.x() <= m_topRight.x() 
		&& point.y() >= m_bottomLeft.y() && point.y() <= m_topRight.y();
}