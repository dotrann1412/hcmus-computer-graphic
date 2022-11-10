#include "Rectangle.h"


Rectangle::Rectangle(const Point& rect_start, const Point& rect_end) 
	: Shape(rect_start, rect_end) {

};

Rectangle::Rectangle(const Rectangle& another) 
	: Shape(another) {

};

void Rectangle::render(bool iz_fill, std::function<void(const int&, const int&, const Pixel&)> setPixelCallback)
{
	Point topLeft = {m_bottomLeft.x(), m_topRight.y()}, bottomRight = {m_topRight.x(), m_bottomLeft.y()};
	Shape::bresenham(m_bottomLeft, topLeft, m_boundaryColor, setPixelCallback);
	Shape::bresenham(topLeft, m_topRight, m_boundaryColor, setPixelCallback);
	Shape::bresenham(m_topRight, bottomRight, m_boundaryColor, setPixelCallback);
	Shape::bresenham(bottomRight, m_bottomLeft, m_boundaryColor, setPixelCallback);
	if (fill) 
		boundary_fill();
}

bool Rectangle::contain(const Point& point) {
	return Shape::contain(point);
}