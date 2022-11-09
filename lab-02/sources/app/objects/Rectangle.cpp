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
	glColor3ui(m_color.R, m_color.G, m_color.B);  
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
		glVertex2f(m_bottomLeft.x(), m_bottomLeft.y());
		glVertex2f(m_bottomLeft.x(), m_topRight.y());
		glVertex2f(m_topRight.x(), m_topRight.y());
		glVertex2f(m_topRight.x(), m_bottomLeft.y());
	glEnd();
}

bool Rectangle::contain(const Point& point) {
	return Shape::contain(point);
}