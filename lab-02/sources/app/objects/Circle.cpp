#include "Circle.h"

Circle::Circle(const Point& rect_start, const Point& rect_end, const Color& boundary_color, const Color& fill_color)
	: Elipse(rect_start, rect_end, boundary_color, fill_color) {
	this->m_a = this->m_b = std::min(this->m_a, this->m_b);
}

Circle::Circle(const Circle& another) 
	: Elipse(another) {

}

void Circle::render() const {
	glBegin(GL_POINTS);
    glColor3ub(m_boundaryColor.R, m_boundaryColor.G, m_boundaryColor.B);

    int center_x = m_center.x();
    int center_y = m_center.y();

    glVertex2i(center_x, center_y + m_a);
    glVertex2i(center_x, center_y - m_a);
    glVertex2i(center_x - m_a, center_y);
    glVertex2i(center_x + m_a, center_y);

      k_borderID[center_x][center_y + m_a]
    = k_borderID[center_x][center_y - m_a]
    = k_borderID[center_x - m_a][center_y]
    = k_borderID[center_x + m_a][center_y]
    = m_id;

    int p = 1 - m_a;
    int x = 1;
    int y = m_a;

    while (x < y) {
        if (p < 0) p += 2 * x + 3;  
        else --y, p += 2 * (x - y) + 3;

        glVertex2i(center_x + x, center_y + y); glVertex2i(center_x + y, center_y + x);
        glVertex2i(center_x + x, center_y - y); glVertex2i(center_x + y, center_y - x);
        glVertex2i(center_x - x, center_y + y); glVertex2i(center_x - y, center_y + x);
        glVertex2i(center_x - x, center_y - y); glVertex2i(center_x - y, center_y - x);

        k_borderID[center_x + x][ center_y + y] = k_borderID[center_x + y][ center_y + x] =
        k_borderID[center_x + x][ center_y - y] = k_borderID[center_x + y][ center_y - x] =
        k_borderID[center_x - x][ center_y + y] = k_borderID[center_x - y][ center_y + x] =
        k_borderID[center_x - x][ center_y - y] = k_borderID[center_x - y][ center_y - x] = m_id;

        ++x;
    }

    glEnd();
    
    if (m_fillColor != Color::WHITE)
        boundary_fill();
}

void Circle::unbound() {
    int center_x = m_center.x();
    int center_y = m_center.y();
    k_borderID[center_x][center_y + m_a] = k_borderID[center_x][center_y - m_a] = 
    k_borderID[center_x - m_a][center_y] = k_borderID[center_x + m_a][center_y] = 0;

    int p = 1 - m_a;
    int x = 1;
    int y = m_a;

    while (x < y) {
        if (p < 0) p += 2 * x + 3;  
        else --y, p += 2 * (x - y) + 3;

        k_borderID[center_x + x][ center_y + y] = k_borderID[center_x + y][ center_y + x] =
        k_borderID[center_x + x][ center_y - y] = k_borderID[center_x + y][ center_y - x] =
        k_borderID[center_x - x][ center_y + y] = k_borderID[center_x - y][ center_y + x] =
        k_borderID[center_x - x][ center_y - y] = k_borderID[center_x - y][ center_y - x] = 0;

        ++x;
    }
}

void Circle::setBoundary(const Point& first, const Point& second)
{
    Elipse::setBoundary(first, second);
	this->m_a = this->m_b = std::min(this->m_a, this->m_b);
}

bool Circle::contain(const Point& pts) {
	return (pts.x() - m_center.x()) * (pts.x() - m_center.x()) + (pts.y() - m_center.y()) * (pts.y() - m_center.y()) <= m_a * m_a;
}