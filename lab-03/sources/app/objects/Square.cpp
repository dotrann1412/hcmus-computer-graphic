#include "Square.h"

Square::Square(const Point& rect_start, const Point& rect_end, const Color& boundary_color, const Color& fill_color) 
	: Rectangle(rect_start, rect_end, boundary_color, fill_color) {
	int32_t side = std::min(m_topRight.x() - m_bottomLeft.x(), m_topRight.y() - m_bottomLeft.y());
	m_bottomLeft = {m_bottomLeft.x(), m_topRight.y() - side};
	m_topRight = {m_bottomLeft.x() + side, m_topRight.y()};
}

Square::Square(const Square& another) 
	: Rectangle(another) {

}

void Square::setBoundary(const Point& first, const Point& last) {
	Shape::setBoundary(first, last);
	int32_t side = std::min(m_topRight.x() - m_bottomLeft.x(), m_topRight.y() - m_bottomLeft.y());
	m_bottomLeft = {m_bottomLeft.x(), m_topRight.y() - side};
	m_topRight = {m_bottomLeft.x() + side, m_topRight.y()};
}