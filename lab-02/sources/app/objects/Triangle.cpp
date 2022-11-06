#include "Triangle.h"

Triangle::Triangle(const Point& rect_start, const Point& rect_end) 
	: Shape(rect_start, rect_end) {

}


Triangle::Triangle(const Triangle& another) 
	: Shape(another) {

}

void Triangle::render() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(m_bottomLeft.x(), m_bottomLeft.y());
		glVertex2f((m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y());
		glVertex2f(m_topRight.x(), m_bottomLeft.y());
	glEnd();
}

bool Triangle::contain(const Point& another) {
	return true;
}