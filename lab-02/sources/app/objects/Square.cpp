#include "Square.h"


Square::Square(const Point& rect_start, const Point& rect_end) 
	: Rectangle(rect_start, rect_end) {
	float side = std::min(m_topRight.x() - m_bottomLeft.x(), m_topRight.y() - m_bottomLeft.y());
	m_topRight = {m_bottomLeft.x() + side, m_bottomLeft.y() + side};
}

Square::Square(const Square& another) 
	: Rectangle(another) {

}