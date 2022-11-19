#include "Plus.h"
#include "Line.h"
#include "helpers.h"

Plus::Plus(const Point& rect_start, const Point& rect_end, 
    const Color& boundary_color, const Color& fill_color) 
: Shape (rect_start, rect_end, boundary_color, fill_color) {

}

Plus::Plus(const Plus& another)
: Shape (another) {

}

void Plus::render() const {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_topRight.y()),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_topRight.y()),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham(boundary[i], boundary[(i + 1) % n]);
    }

    boundary_fill();
}

bool Plus::contain(const Point& point) {
    if (!Shape::contain(point))
        return false;
    std::vector<Line> line = {};
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_topRight.y()),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_topRight.y()),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3),
    };
    
    for (int i = 0, n = boundary.size(); i < n; ++i) {
        line.push_back({boundary[i], boundary[(i + 1) % n]});
    }

    return inside(point, line);
}

void Plus::setBoundary(const Point& first, const Point& second) {
    Shape::setBoundary (first, second);
}

void Plus::unbound() {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_topRight.y()),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_topRight.y()),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham_rev(boundary[i], boundary[(i + 1) % n]);
    }
}