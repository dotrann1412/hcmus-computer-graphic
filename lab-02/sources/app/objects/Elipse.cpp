#include "Elipse.h"

Elipse::Elipse(const Point& rect_start, const Point& rect_end)
	: Shape(rect_start, rect_end) {
	this->m_center = {(m_bottomLeft.x() + m_topRight.x()) / 2, (m_bottomLeft.y() + m_topRight.y()) / 2};
	this->m_a = (m_topRight.x() - m_bottomLeft.x()) / 2;
	this->m_b = (m_topRight.y() - m_bottomLeft.y()) / 2;
}

Elipse::Elipse(const Elipse& another)
	: Shape(another) {

}

Elipse::~Elipse() {

}

void Elipse::render() {
	glBegin(GL_POINTS);
    
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
}


bool Elipse::contain(const Point& ) {
	return true;
}