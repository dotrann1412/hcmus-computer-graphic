#include "Shape.h"

#include "cmath"

#include <functional>
#include <iostream>
#include <queue>

Shape::Shape(const Point& rect_start, const Point& rect_end, const int& id) {
	m_bottomLeft = {std::min(rect_start.x(), rect_end.x()), std::min(rect_start.y(), rect_end.y())};
	m_topRight = {std::max(rect_start.x(), rect_end.x()), std::max(rect_start.y(), rect_end.y())};
	m_color = Color::BLUE;
	m_id = id;
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

void Shape::boundary_fill(std::function<void(const int&, const int&, const Pixel&)> set_pixel) {
	static int dx[] = {1, -1, 0, 0};
	static int dy[] = {0, 0, 1, -1};

    Pixel pix = {m_fillColor.R, m_fillColor.G, m_fillColor.B, 0};
    
}

void Shape::bresenham(cosnt Point& first, const Point& last, const Color& color, std::function<void(const int&, const int&, const Pixel&)> set_pixel)
{
	if (first > last)
        swap(first, last);
    
    int dx = last.x() - first.x();
    int dy = last.y() - first.y();
    
    bool is_negative_slope = false;
    if (dy < 0) dy = -dy, is_negative_slope = true;

    Pixel pix = {color.R, color.G, color.B, id};

    glBegin(GL_POINTS);
    if (dx > dy) {
        int p = 2 * dy - dx;
        const int A = 2 * dy;
        const int B = 2 * (dy - dx);

        int interval = 1;
        if (is_negative_slope) interval = -1;
        
        for (int x = first.x(), y = first.y(); x <= last.x(); ++x) {
            if (p <= 0) p += A;
            else p += B, y += interval;
            glVertex2i(x, y);
            k_color_map[x][y] = pix;
        }
    }
    else {
        int p = 2 * dx - dy;
        const int A = 2 * dx;
        const int B = 2 * (dx - dy);

        int interval = 1;
        if (is_negative_slope) interval = -1;

        for (int x = first.x(), y = first.y(); y != last.y() + interval; y += interval) {
            if (p <= 0) p += A;
            else p += B, ++x;
            glVertex2i(x, y);
            k_color_map[x][y] = pix;
        }
    }
	glEnd();
}

Point Shape::center() const {
	return {(m_bottomLeft.x() + m_topRight.x()) / 2, (m_bottomLeft.y() + m_topRight.y()) / 2};
}

