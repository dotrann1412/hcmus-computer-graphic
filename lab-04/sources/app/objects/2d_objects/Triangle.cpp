#include "Triangle.h"
#include "Line.h"
#include <vector>

Triangle::Triangle(const Point& rect_start, const Point& rect_end, const Color& boundary_color, const Color& fill_color) 
	: Shape2D(rect_start, rect_end, boundary_color, fill_color) {

}

Triangle::Triangle(const Triangle& another) 
	: Shape2D(another) {

}

void Triangle::render() const {
    glPointSize(m_pointSize);
	Point top = {(m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y()};
	std::vector<Point> boundary = {
		Point(top),
		{m_topRight.x(), m_bottomLeft.y()},
		m_bottomLeft
	};

	for (int i = 0, n = boundary.size(); i < n; ++i) {
		bresenham(boundary[i], boundary[(i + 1) % n]);
	}

	boundary_fill();
}

void Triangle::unbound() {
	Point top = { (m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y() };
	std::vector<Point> boundary = {
		Point(top),
		{m_topRight.x(), m_bottomLeft.y()},
		m_bottomLeft
	};

	for (int i = 0, n = boundary.size(); i < n; ++i) {
		bresenham_rev(boundary[i], boundary[(i + 1) % n]);
	}
}

bool Triangle::contain(const Point& point) {
    if (!Shape2D::contain(point))
        return false;
    
	std::vector<Line> line = {};
	Point top = { (m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y() };

    std::vector<Point> boundary = {
		Point(top),
		{m_topRight.x(), m_bottomLeft.y()},
		m_bottomLeft
    };
	
	for (auto& x: boundary)
		x = x.transform(m_trans);

    return inside(point, boundary);
}