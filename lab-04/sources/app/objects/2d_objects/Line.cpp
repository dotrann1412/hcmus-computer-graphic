#include "Line.h"
#include <iostream>

Line::Line(): Shape({0, 0}, {0, 0}) {
	this->m_start = this->m_end = Point(0, 0);
}

Line::Line(const Point& a, const Point& b, const Color& boundary_color, const Color& fill_color)
	: Shape(a, b, boundary_color, fill_color) {
	this->m_start = a;
	this->m_end = b;
}

Line::Line(const Line& another): Shape(another) {
	this->m_start = another.m_start;
	this->m_end = another.m_end;
}

Line::~Line() {

}

Point Line::getStartingPoint() const {
	return this->m_start;
}

Point Line::getEndingPoint() const {
	return this->m_end;
}

void Line::setStartingPoint(Point a) {
	this->m_start = a;
}

void Line::setEndingPoint(Point b) {
	this->m_end = b;
}

std::string Line::to_string() const {
	return "[" + this->m_start.to_string() + " - " + this->m_end.to_string() + "]";
}

//return euclid distance between starting point and ending point
float Line::length() const {
	float changeX = this->m_start.x() - this->m_end.x();
	float changeY = this->m_start.y() - this->m_end.y();
	return sqrt(pow(changeX, 2) + pow(changeY, 2));
}

void Line::render() const {
    glPointSize(m_pointSize);
	Shape::bresenham(m_start, m_end);
}

void Line::unbound() {
	Shape::bresenham_rev(m_start, m_end);
}

void Line::setBoundary(const Point& first, const Point& second) {
	this->m_start = first;
	this->m_end = second;
	unbound();
}

bool Line::contain(const Point& pts) {
	const static float K = 1;
	return Shape::contain(pts) && abs(pts.x() - m_start.x()) * (m_end.y() - m_start.y()) - (pts.y() - m_start.y()) * (m_end.y() - m_start.y()) < K;
}