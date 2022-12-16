#include "Times.h"
#include "Line.h"

Times::Times(const Point& rect_start, const Point& rect_end, 
    const Color& boundary_color, const Color& fill_color) 
: Shape (rect_start, rect_end, boundary_color, fill_color) {

}

Times::Times(const Times& another)
: Shape (another) {

}

void Times::render() const {
    glPointSize(m_pointSize);
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() , m_bottomLeft.y() + 1.0 * h_side / 5),
        Point(m_bottomLeft.x() + 1.0 * v_side / 5, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 2, m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x() + 4.0 * v_side / 5, m_bottomLeft.y()),
        Point(m_topRight.x() , m_bottomLeft.y() + 1.0 * h_side / 5),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 2),
        Point(m_topRight.x(), m_bottomLeft.y() + 4.0 * h_side / 5),
        Point(m_bottomLeft.x() + 4.0 * v_side / 5, m_topRight.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 2, m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 1.0 * v_side / 5, m_topRight.y()),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 4.0 * h_side / 5),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 2),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham(boundary[i], boundary[(i + 1) % n]);
    }

    boundary_fill();
}

bool Times::contain(const Point& point) {
    if (!Shape::contain(point))
        return false;
    std::vector<Line> line = {};
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() , m_bottomLeft.y() + 1.0 * h_side / 5),
        Point(m_bottomLeft.x() + 1.0 * v_side / 5, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 2, m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x() + 4.0 * v_side / 5, m_bottomLeft.y()),
        Point(m_topRight.x() , m_bottomLeft.y() + 1.0 * h_side / 5),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 2),
        Point(m_topRight.x(), m_bottomLeft.y() + 4.0 * h_side / 5),
        Point(m_bottomLeft.x() + 4.0 * v_side / 5, m_topRight.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 2, m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 1.0 * v_side / 5, m_topRight.y()),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 4.0 * h_side / 5),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 2),
    };

    for (auto& x: boundary)
        x = x.transform(m_trans);

    return inside(point, boundary);
}

void Times::setBoundary(const Point& first, const Point& second) {
    Shape::setBoundary (first, second);
}

void Times::unbound() {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x() , m_bottomLeft.y() + 1.0 * h_side / 5),
        Point(m_bottomLeft.x() + 1.0 * v_side / 5, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 2, m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x() + 4.0 * v_side / 5, m_bottomLeft.y()),
        Point(m_topRight.x() , m_bottomLeft.y() + 1.0 * h_side / 5),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 2),
        Point(m_topRight.x(), m_bottomLeft.y() + 4.0 * h_side / 5),
        Point(m_bottomLeft.x() + 4.0 * v_side / 5, m_topRight.y()),
        Point(m_bottomLeft.x() + 1.0 * v_side / 2, m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 1.0 * v_side / 5, m_topRight.y()),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 4.0 * h_side / 5),
        Point(m_bottomLeft.x() + 1.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 2),
    };

    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham_rev(boundary[i], boundary[(i + 1) % n]);
    }
}