#include "Triangle.h"
#include "Line.h"
#include <vector>

Triangle::Triangle(const Point& rect_start, const Point& rect_end) 
	: Shape(rect_start, rect_end) {

}

Triangle::Triangle(const Triangle& another) 
	: Shape(another) {

}

void Triangle::render() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3ui(m_color.R, m_color.G, m_color.B);  
	glLineWidth(3.0);
	glBegin(GL_POLYGON);
		glVertex2f(m_bottomLeft.x(), m_bottomLeft.y());
		glVertex2f((m_bottomLeft.x() + m_topRight.x()) / 2, m_topRight.y());
		glVertex2f(m_topRight.x(), m_bottomLeft.y());
	glEnd();
}

bool Triangle::contain(const Point& pts) {
	auto intersect = [] (const Line& line, const Point& trickly)-> bool {
		float y1 = line.getStartingPoint().y(), y2 = line.getEndingPoint().y();
		float x1 = line.getStartingPoint().x(), x2 = line.getEndingPoint().x();
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