#include "Circle.h"

Circle::Circle(const Point& rect_start, const Point& rect_end)
	: Elipse(rect_start, rect_end) {
	this->m_a = this->m_b = std::min(this->m_a, this->m_b);
}

Circle::Circle(const Circle& another) 
	: Elipse(another) {

}

void Circle::render(bool fill, std::function<void(const int&, const int&, const Pixel&)> setPixelCallback) {
	glBegin(GL_POINTS);
    glColor3ui(m_color.R, m_color.G, m_color.B);

    int center_x = m_center.x(); // move here for faster computing
    int center_y = m_center.y();

    Pixel pix = {m_boundaryColor.R, m_boundaryColor.G, m_boundaryColor.B, m_id};

    setPixelCallback(center_x, center_y + m_a, pix);
    setPixelCallback(center_x, center_y - m_a, pix);
    setPixelCallback(center_x - m_a, center_y, pix);
    setPixelCallback(center_x + m_a, center_y, pix);

    int p = 1 - m_a;
    int x = 1;
    int y = m_a;

    while (x < y) {
        if (p < 0) p += 2 * x + 3;  
        else --y, p += 2 * (x - y) + 3;

        setPixelCallback(center_x + x, center_y + y, pix); 
        setPixelCallback(center_y + y, center_x + x, pix);
        setPixelCallback(center_x + x, center_y - y, pix); 
        setPixelCallback(center_y + y, center_x - x, pix);
        setPixelCallback(center_x - x, center_y + y, pix); 
        setPixelCallback(center_y - y, center_x + x, pix);
        setPixelCallback(center_x - x, center_y - y, pix); 
        setPixelCallback(center_y - y, center_x - x, pix);

        ++x;
    }

    glEnd();
}

bool Circle::contain(const Point& pts) {
	return (pts.x() - m_center.x()) * (pts.x() - m_center.x()) + (pts.y() - m_center.y()) * (pts.y() - m_center.y()) <= m_a * m_a;
}