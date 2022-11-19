#include "Star.h"
#include "Line.h"
#include "helpers.h"

Star::Star(const Point& rect_start, const Point& rect_end, 
    const Color& boundary_color, const Color& fill_color) 
: Shape (rect_start, rect_end, boundary_color, fill_color) {

}

Star::Star(const Star& another)
: Shape (another) {

}

void Star::render() const {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() + v_side / 2, m_topRight.y()),
        Point(m_bottomLeft.x() + 9.0 * v_side / 14, m_bottomLeft.y() + 9.0 * h_side / 14),
        Point(m_topRight.x(), m_bottomLeft.y() + 17.0 * h_side / 28),
        Point(m_bottomLeft.x() + 3.0 * v_side / 4, m_bottomLeft.y() + 5.0 * h_side / 14),
        Point(m_bottomLeft.x() + 6.0 * v_side / 7, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 2, m_bottomLeft.y() + 5.0 * h_side / 28),
        Point(m_bottomLeft.x() + 1.0 * v_side / 7, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 4, m_bottomLeft.y() + 5.0 * h_side / 14),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 17.0 * h_side / 28),
        Point(m_bottomLeft.x() + 5.0 * v_side / 14, m_bottomLeft.y() + 9.0 * h_side / 14),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham(boundary[i], boundary[(i + 1) % n]);
    }

    boundary_fill();
}

bool Star::contain(const Point& point) {
    if (!Shape::contain(point))
        return false;
    std::vector<Line> line = {};
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() + v_side / 2, m_topRight.y()),
        Point(m_bottomLeft.x() + 9.0 * v_side / 14, m_bottomLeft.y() + 9.0 * h_side / 14),
        Point(m_topRight.x(), m_bottomLeft.y() + 17.0 * h_side / 28),
        Point(m_bottomLeft.x() + 3.0 * v_side / 4, m_bottomLeft.y() + 5.0 * h_side / 14),
        Point(m_bottomLeft.x() + 6.0 * v_side / 7, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 2, m_bottomLeft.y() + 5.0 * h_side / 28),
        Point(m_bottomLeft.x() + 1.0 * v_side / 7, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 4, m_bottomLeft.y() + 5.0 * h_side / 14),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 17.0 * h_side / 28),
        Point(m_bottomLeft.x() + 5.0 * v_side / 14, m_bottomLeft.y() + 9.0 * h_side / 14),
    };
    
    for (int i = 0, n = boundary.size(); i < n; ++i) {
        line.push_back({boundary[i], boundary[(i + 1) % n]});
    }

    return inside(point, line);
}

void Star::setBoundary(const Point& first, const Point& second) {
    Shape::setBoundary (first, second);
}

void Star::unbound() {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() + v_side / 2, m_topRight.y()),
        Point(m_bottomLeft.x() + 9.0 * v_side / 14, m_bottomLeft.y() + 9.0 * h_side / 14),
        Point(m_topRight.x(), m_bottomLeft.y() + 17.0 * h_side / 28),
        Point(m_bottomLeft.x() + 3.0 * v_side / 4, m_bottomLeft.y() + 5.0 * h_side / 14),
        Point(m_bottomLeft.x() + 6.0 * v_side / 7, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 2, m_bottomLeft.y() + 5.0 * h_side / 28),
        Point(m_bottomLeft.x() + 1.0 * v_side / 7, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 4, m_bottomLeft.y() + 5.0 * h_side / 14),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 17.0 * h_side / 28),
        Point(m_bottomLeft.x() + 5.0 * v_side / 14, m_bottomLeft.y() + 9.0 * h_side / 14),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham_rev(boundary[i], boundary[(i + 1) % n]);
    }
}