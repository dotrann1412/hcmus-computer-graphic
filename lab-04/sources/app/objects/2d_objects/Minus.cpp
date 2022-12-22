#include "Minus.h"
#include "Line.h"

Minus::Minus(const Point& rect_start, const Point& rect_end, 
    const Color& boundary_color, const Color& fill_color) 
: Shape2D (rect_start, rect_end, boundary_color, fill_color) {

}

Minus::Minus(const Minus& another)
: Shape2D (another) {

}

void Minus::render() const {
    glPointSize(m_pointSize);
    glPointSize(m_pointSize);
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham(boundary[i], boundary[(i + 1) % n]);
    }

    boundary_fill();
}

bool Minus::contain(const Point& point) {
    if (!Shape2D::contain(point))
        return false;

    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
    };

    for (auto& x: boundary)
        x = x.transform(m_trans);

    return inside(point, boundary);
}

void Minus::setBoundary(const Point& first, const Point& second) {
    Shape2D::setBoundary (first, second);
}

void Minus::unbound() {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham_rev(boundary[i], boundary[(i + 1) % n]);
    }
}