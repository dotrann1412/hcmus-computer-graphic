#include "Shape.h"

#include "cmath"

Shape::Shape(const Point& rect_start, const Point& rect_end) {
	m_bottomLeft = {std::min(rect_start.x(), rect_end.x()), std::min(rect_start.y(), rect_end.y())};
	m_topRight = {std::max(rect_start.x(), rect_end.x()), std::max(rect_start.y(), rect_end.y())};
	m_color = Color::BLUE;
}

Shape::Shape(const Shape& another) {
	m_bottomLeft = another.m_bottomLeft;
	m_topRight = another.m_topRight;
	m_color = another.m_color;
}

Shape::~Shape() {
	// do nothing
}


bool Shape::contain(const Point& point) {
	return point.x() >= m_bottomLeft.x() && point.x() <= m_topRight.x() 
		&& point.y() >= m_bottomLeft.y() && point.y() <= m_topRight.y();
}

#include <functional>
#include <iostream>
#include <queue>

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void boundary_fill(int x, int y, Color boundary_color, Color fill_color, int depth = 0) {
	if (depth == 100)
		return;
	uint8_t f[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, f);
	if ((f[0] != boundary_color.R) && (f[0] != fill_color.R) && (f[1] != boundary_color.G) && (f[1] != fill_color.G) && (f[2] != boundary_color.B) && (f[2] != fill_color.B)) {
		
		glBegin(GL_POINTS);
		glColor3ub(fill_color.R, fill_color.G, fill_color.B);
		glVertex2i(x, y);
		glEnd();
		glFlush();

		boundary_fill(x, y + 1, boundary_color, fill_color, depth + 1);
		boundary_fill(x + 1, y, boundary_color, fill_color, depth + 1);
		boundary_fill(x, y - 1, boundary_color, fill_color, depth + 1);
		boundary_fill(x - 1, y, boundary_color, fill_color, depth + 1);
	}
}

void Shape::fill(const Color& color) {
	
}

Point Shape::center() const {
	return {(m_bottomLeft.x() + m_topRight.x()) / 2, (m_bottomLeft.y() + m_topRight.y()) / 2};
}