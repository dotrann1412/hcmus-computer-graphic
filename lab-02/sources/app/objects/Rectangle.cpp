#include "Rectangle.h"


Rectangle::Rectangle(const Point& rect_start, const Point& rect_end) 
	: Shape(rect_start, rect_end) {

};

Rectangle::Rectangle(const Rectangle& another) 
	: Shape(another) {

};

void Rectangle::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(m_bottomLeft.x(), m_bottomLeft.y());
		glVertex2f(m_bottomLeft.x(), m_topRight.y());
		glVertex2f(m_topRight.x(), m_topRight.y());
		glVertex2f(m_topRight.x(), m_bottomLeft.y());
	glEnd();
}

bool Rectangle::contain(const Point& point) {
	return true;
}