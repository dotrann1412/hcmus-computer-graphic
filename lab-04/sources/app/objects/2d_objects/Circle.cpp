#include "Circle.h"

#include <algorithm>

Circle::Circle(const Point& rect_start, const Point& rect_end, const Color& boundary_color, const Color& fill_color)
	: Elipse(rect_start, rect_end, boundary_color, fill_color) {
    int32_t side = min(m_topRight.x() - m_bottomLeft.x(), m_topRight.y() - m_bottomLeft.y());
    m_bottomLeft = { m_bottomLeft.x(), m_topRight.y() - side };
    m_topRight = { m_bottomLeft.x() + side, m_topRight.y() };
	this->m_a = this->m_b = min(this->m_a, this->m_b);
}

Circle::Circle(const Circle& another) 
	: Elipse(another) {

}

void Circle::render() const {
    glPointSize(m_pointSize);
	glBegin(GL_POINTS);
    glColor3ub(m_boundaryColor.R, m_boundaryColor.G, m_boundaryColor.B);

    int center_x = m_center.x();
    int center_y = m_center.y();

    setPixel(center_x, center_y + m_a);
    setPixel(center_x, center_y - m_a);
    setPixel(center_x - m_a, center_y);
    setPixel(center_x + m_a, center_y);

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

        setPixel(center_x + x, center_y + y); setPixel(center_x + y, center_y + x);
        setPixel(center_x + x, center_y - y); setPixel(center_x + y, center_y - x);
        setPixel(center_x - x, center_y + y); setPixel(center_x - y, center_y + x);
        setPixel(center_x - x, center_y - y); setPixel(center_x - y, center_y - x);

        k_borderID[center_x + x][ center_y + y] = k_borderID[center_x + y][ center_y + x] =
        k_borderID[center_x + x][ center_y - y] = k_borderID[center_x + y][ center_y - x] =
        k_borderID[center_x - x][ center_y + y] = k_borderID[center_x - y][ center_y + x] =
        k_borderID[center_x - x][ center_y - y] = k_borderID[center_x - y][ center_y - x] = m_id;

        ++x;
    }

    glEnd();
    
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
    Point _center = m_center.transform(m_trans);
    int _radius = Point(_center.x(), m_topRight.y()).transform(m_trans).y() - _center.y();
	return Shape::contain(pts) && (pts.x() - _center.x()) * (pts.x() - _center.x()) + (pts.y() - _center.y()) * (pts.y() - _center.y()) <= _radius * _radius;
}