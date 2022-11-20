#include "Hexagon.h"
#include "Line.h"

Hexagon::Hexagon(const Point& rect_start, const Point& rect_end, 
    const Color& boundary_color, const Color& fill_color) 
: Shape (rect_start, rect_end, boundary_color, fill_color) {

}

Hexagon::Hexagon(const Hexagon& another)
: Shape (another) {

}

void Hexagon::render() const {
    glPointSize(m_pointSize);
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() + v_side / 2, m_topRight.y()),
        Point(m_topRight.x(), m_bottomLeft.y() + 3.0 * h_side / 4),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 4),
        Point(m_bottomLeft.x() + v_side / 2, m_bottomLeft.y()),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 4),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 3.0 * h_side / 4),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham(boundary[i], boundary[(i + 1) % n]);
    }

    boundary_fill();
}

bool Hexagon::contain(const Point& point) {
    if (!Shape::contain(point))
        return false;
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();

    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() + v_side / 2, m_topRight.y()),
        Point(m_topRight.x(), m_bottomLeft.y() + 3.0 * h_side / 4),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 4),
        Point(m_bottomLeft.x() + v_side / 2, m_bottomLeft.y()),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 4),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 3.0 * h_side / 4),
    };

    for (auto& x: boundary) 
        x = x.transform(m_trans);

    return inside(point, boundary);
}

void Hexagon::setBoundary(const Point& first, const Point& second) {
    Shape::setBoundary (first, second);
}

void Hexagon::unbound() {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() + v_side / 2, m_topRight.y()),
        Point(m_topRight.x(), m_bottomLeft.y() + 3.0 * h_side / 4),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 4),
        Point(m_bottomLeft.x() + v_side / 2, m_bottomLeft.y()),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 4),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 3.0 * h_side / 4),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham_rev(boundary[i], boundary[(i + 1) % n]);
    }
}