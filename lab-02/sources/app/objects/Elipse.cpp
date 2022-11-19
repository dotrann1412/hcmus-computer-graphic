#include "Elipse.h"

Elipse::Elipse(const Point& rect_start, const Point& rect_end, const Color& boundary_color, const Color& fill_color)
	: Shape(rect_start, rect_end, boundary_color, fill_color) {
	this->m_center = {(m_bottomLeft.x() + m_topRight.x()) / 2, (m_bottomLeft.y() + m_topRight.y()) / 2};
	this->m_a = (m_topRight.x() - m_bottomLeft.x()) / 2;
	this->m_b = (m_topRight.y() - m_bottomLeft.y()) / 2;
}

Elipse::Elipse(const Elipse& another)
	: Shape(another) {

}

Elipse::~Elipse() {

}

void Elipse::render() const {
	glBegin(GL_POINTS);
    glColor3ub(m_boundaryColor.R, m_boundaryColor.G, m_boundaryColor.B);

    int x = 0, y = m_b;
    int64_t m_a_squared = m_a * m_a;
    int64_t m_b_squared = m_b * m_b;
    int64_t dx = 2ll * m_b_squared * x;
    int64_t dy = 2ll * m_a_squared * y;

    int center_x = m_center.x();
    int center_y = m_center.y();

    int64_t p1 = m_b_squared - m_a_squared * m_b + 0.25f * m_a_squared;


    while (dx < dy) {

        glVertex2i(center_x + x, center_y + y);
        glVertex2i(center_x + x, center_y - y);
        glVertex2i(center_x - x, center_y + y);
        glVertex2i(center_x - x, center_y - y);

          k_borderID[center_x + x][center_y + y]
        = k_borderID[center_x + x][center_y - y]
        = k_borderID[center_x - x][center_y + y]
        = k_borderID[center_x - x][center_y - y] 
        = m_id;


        if (p1 < 0) {
            dx += 2ll * m_b_squared;
            p1 += dx + m_b_squared;
        }
        else {
            --y;
            dx += 2ll * m_b_squared;
            dy -= 2ll * m_a_squared;
            p1 += dx - dy + m_b_squared;
        }

        ++x;
    }

    int64_t p2 = m_b_squared * (1.0f * x + 0.5f) * (1.0f * x + 0.5f) + m_a_squared * (y - 1) * (y - 1) - m_a_squared * m_b_squared;
    while (y >= 0) {
        glVertex2i(center_x + x, center_y + y);
        glVertex2i(center_x + x, center_y - y);
        glVertex2i(center_x - x, center_y + y);
        glVertex2i(center_x - x, center_y - y);

          k_borderID[center_x + x][center_y + y]
        = k_borderID[center_x + x][center_y - y]
        = k_borderID[center_x - x][center_y + y]
        = k_borderID[center_x - x][center_y - y] 
        = m_id;
        
        if (p2 > 0) {
            dy -= 2ll * m_a_squared;
            p2 += m_a_squared - dy;
        }
        else {
            ++x;
            dx += 2 * m_b_squared;
            dy -= 2 * m_a_squared;
            p2 += dx - dy + m_a_squared;
        }

        --y;
    }

    glEnd();

    boundary_fill();
}

void Elipse::unbound() {
    int x = 0, y = m_b;
    int64_t m_a_squared = m_a * m_a;
    int64_t m_b_squared = m_b * m_b;
    int64_t dx = 2ll * m_b_squared * x;
    int64_t dy = 2ll * m_a_squared * y;

    int center_x = m_center.x();
    int center_y = m_center.y();

    int64_t p1 = m_b_squared - m_a_squared * m_b + 0.25f * m_a_squared;

    while (dx < dy) {
          k_borderID[center_x + x][center_y + y]
        = k_borderID[center_x + x][center_y - y]
        = k_borderID[center_x - x][center_y + y]
        = k_borderID[center_x - x][center_y - y] 
        = 0;


        if (p1 < 0) {
            dx += 2ll * m_b_squared;
            p1 += dx + m_b_squared;
        }
        else {
            --y;
            dx += 2ll * m_b_squared;
            dy -= 2ll * m_a_squared;
            p1 += dx - dy + m_b_squared;
        }

        ++x;
    }

    int64_t p2 = m_b_squared * (1.0f * x + 0.5f) * (1.0f * x + 0.5f) + m_a_squared * (y - 1) * (y - 1) - m_a_squared * m_b_squared;
    while (y >= 0) {
          k_borderID[center_x + x][center_y + y]
        = k_borderID[center_x + x][center_y - y]
        = k_borderID[center_x - x][center_y + y]
        = k_borderID[center_x - x][center_y - y]
        = 0;
        
        if (p2 > 0) {
            dy -= 2ll * m_a_squared;
            p2 += m_a_squared - dy;
        }
        else {
            ++x;
            dx += 2 * m_b_squared;
            dy -= 2 * m_a_squared;
            p2 += dx - dy + m_a_squared;
        }

        --y;
    }
}

void Elipse::setBoundary(const Point& first, const Point& second)
{
    Shape::setBoundary(first, second);
    this->m_center = {(m_bottomLeft.x() + m_topRight.x()) / 2, (m_bottomLeft.y() + m_topRight.y()) / 2};
	this->m_a = (m_topRight.x() - m_bottomLeft.x()) / 2;
	this->m_b = (m_topRight.y() - m_bottomLeft.y()) / 2;
}

bool Elipse::contain(const Point& pts) {
    if (!Shape::contain(pts))
        return false;
	return (pts.x() - m_center.x()) * (pts.x() - m_center.x()) * (m_b * m_b)+ (pts.y() - m_center.y()) * (pts.y() - m_center.y()) *  (m_a * m_a)  <=  (m_a * m_a) *  (m_b * m_b);
}