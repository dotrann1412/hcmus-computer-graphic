#include "Triangle.h"
#include "Line.h"
#include <vector>

Triangle::Triangle(const Point& rect_start, const Point& rect_end, const Color& boundary_color, const Color& fill_color) 
	: Shape(rect_start, rect_end, boundary_color, fill_color) {

}

Triangle::Triangle(const Triangle& another) 
	: Shape(another) {

}

void Triangle::render() const {
	Point top = {(m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y()};
	
	bresenham(m_bottomLeft, top);
	bresenham(top, {m_topRight.x(), m_bottomLeft.y()});
	bresenham(m_bottomLeft, {m_topRight.x(), m_bottomLeft.y()});

	if (m_fillColor != Color::WHITE)
		boundary_fill();
}

void Triangle::unbound() {
	Point top = {(m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y()};
	bresenham_rev(m_bottomLeft, top);
	bresenham_rev(top, {m_topRight.x(), m_bottomLeft.y()});
	bresenham_rev(m_bottomLeft, {m_topRight.x(), m_bottomLeft.y()});
}

bool Triangle::contain(const Point& pts) {
	auto intersect = [] (const Line& line, const Point& trickly)-> bool {
		int32_t y1 = line.getStartingPoint().y(), y2 = line.getEndingPoint().y();
		int32_t x1 = line.getStartingPoint().x(), x2 = line.getEndingPoint().x();
		float k = (trickly.y() - y1) / (y2 - y1);

		if (k < 0 || k > 1)
			return false;
		
		float x_expected = x1 * k - (1 - k) * x2;

		return x_expected >= trickly.x();
	};

	std::vector<Line> lines = {
		Line({(m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y()}, {m_bottomLeft.x(), m_bottomLeft.y()}),
		Line({(m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y()}, {m_topRight.x(), m_bottomLeft.y()})
	};

	int count = pts.x() == (m_bottomLeft.x() + m_topRight.x()) / 2 && pts.y() == m_topRight.y();

	for (const Line& x: lines)
		count += intersect(x, pts);

	return Shape::contain(pts) && (count & 1);
}