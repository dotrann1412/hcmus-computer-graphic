#include "Arrow.h"
#include "Line.h"
#include "./helpers.h"

Arrow::Arrow(const Point& rect_start, const Point& rect_end,  const Color& boundary_colors, const Color& fill_colors)
    : Shape(rect_start, rect_end, boundary_colors, fill_colors)
{

}

Arrow::Arrow(const Arrow& another)
    : Shape(another)
{
    
}

void Arrow::render() const
{
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_topRight.y()),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 2),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3)
    };
    
    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham(boundary[i], boundary[(i + 1) % n]);
    }

    boundary_fill();
}

bool Arrow::contain(const Point& pts)
{
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    
    std::vector<Line> boundary = {
        {Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3), Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3)},
        {Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3), Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3)},
        {Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3), Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_topRight.y())},
        {Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_topRight.y()), Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 2)},
        {Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 2), Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y())},
        {Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y()), Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3)},
        {Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3), Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3)}
    };

    return inside(pts, boundary);
}

void Arrow::setBoundary(const Point& first, const Point& second) {
    Shape::setBoundary(first, second);
}

void Arrow::unbound() {
    int h_side = m_topRight.y() - m_bottomLeft.y(), v_side = m_topRight.x() - m_bottomLeft.x();
    
    std::vector<Point> boundary = {
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 1.0 * h_side / 3),
        Point(m_bottomLeft.x(), m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 2.0 * h_side / 3),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_topRight.y()),
        Point(m_topRight.x(), m_bottomLeft.y() + 1.0 * h_side / 2),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y()),
        Point(m_bottomLeft.x() + 2.0 * v_side / 3, m_bottomLeft.y() + 1.0 * h_side / 3)
    };
    
    for (int i = 0, n = boundary.size(); i < n; ++i) {
        bresenham_rev(boundary[i], boundary[(i + 1) % n]);
    }
}
