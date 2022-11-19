#include "Divide.h"
#include "Line.h"
#include "helpers.h"

Divide::Divide(const Point& rect_start, const Point& rect_end, 
    const Color& boundary_color, const Color& fill_color) 
: Shape (rect_start, rect_end, boundary_color, fill_color) {

}

Divide::Divide(const Divide& another)
: Shape (another) {

}

void Divide::render() const {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        m_bottomLeft,
        Point(m_bottomLeft.x() + 1.0 * v_side / 5, m_bottomLeft.y()),
        m_topRight,
        Point(m_bottomLeft.x() + 4.0 * v_side / 5, m_topRight.y()),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham(boundary[i], boundary[(i + 1) % n]);
    }

    boundary_fill();
}

bool Divide::contain(const Point& point) {
    if (!Shape::contain(point))
        return false;
    std::vector<Line> line = {};
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        m_bottomLeft,
        Point(m_bottomLeft.x() + 1.0 * v_side / 5, m_bottomLeft.y()),
        m_topRight,
        Point(m_bottomLeft.x() + 4.0 * v_side / 5, m_topRight.y()),
    };
    
    for (int i = 0, n = boundary.size(); i < n; ++i) {
        line.push_back({boundary[i], boundary[(i + 1) % n]});
    }

    return inside(point, line);
}

void Divide::setBoundary(const Point& first, const Point& second) {
    Shape::setBoundary (first, second);
}

void Divide::unbound() {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        m_bottomLeft,
        Point(m_bottomLeft.x() + 1.0 * v_side / 5, m_bottomLeft.y()),
        m_topRight,
        Point(m_bottomLeft.x() + 4.0 * v_side / 5, m_topRight.y()),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham_rev(boundary[i], boundary[(i + 1) % n]);
    }
}