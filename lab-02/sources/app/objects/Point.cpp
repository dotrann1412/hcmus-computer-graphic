#include "Point.h"

#include <sstream>
#include <iomanip>
#include <math.h>

#include "../utils/string_tokenizer.h"

int Point::k_obj_count = 0;

int Point::instance_count() {
	return Point::k_obj_count;
}

Point::Point() {
	this->m_x = 0;
	this->m_y = 0;
	++Point::k_obj_count;
}

Point::Point(const int32_t& x, const int32_t& y) {
	this->m_x = x;
	this->m_y = y;
	++Point::k_obj_count;
}

Point::Point(const Point& other) {
	this->m_x = other.m_x;
	this->m_y = other.m_y;
	++Point::k_obj_count;
}

int32_t Point::x() const {
	return this->m_x;
}

int32_t Point::y() const {
	return this->m_y;
}

void Point::setx(const int32_t& x) {
	this->m_x = x;
}

void Point::sety(const int32_t& y) {
	this->m_y = y;
}

float Point::distance(const Point& other) const {
	return Point::distance(*this, other);
}

float Point::distance(const Point& a, const Point& b) {
	float changeX = abs(a.m_x - b.m_x);
	float changeY = abs(a.m_y - b.m_y);
	return sqrt(changeX * changeX + changeY * changeY);
}

std::string Point::to_string() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(3) 
		<< "(" <<  this->m_x << ", " << this->m_y << ")";
	return ss.str();
}

std::istream& operator >> (std::istream& s, Point& a) {
	return s >> a.m_x >> a.m_y;
}

std::ostream& operator << (std::ostream& s, const Point& a) {
	return s << a.to_string();
}

Point::~Point() {
	--Point::k_obj_count;
}

Point* Point::parse(std::string s) {
	stringstream ss;
	ss << StringTokenizer::remove(s, ' ');

	string _num;
	getline(ss, _num, '(');
	Point* a = new Point;
	
	getline(ss, _num, ',');
	a->setx(stoi(_num));
	ss >> a->m_y;

	return a;
}

Point* Point::try_parse(std::string s) {
	Point* a = new Point;
	try {
		stringstream ss;

		if(StringTokenizer::parse(s, ",").size() != 2)
			throw "?";

		ss << StringTokenizer::remove(s, ' ');

		string _num;
		getline(ss, _num, '(');
		getline(ss, _num, ',');
		a->setx(stoi(_num));
		getline(ss, _num, ')');
		a->sety(stoi(_num));

	} catch (const void*) {
		delete a;
		return nullptr;
	}
	
	return a;
}

bool Point::operator > (const Point& another) {
	return m_x != another.m_x ? m_x > another.m_x : m_y > another.m_y;
}

bool Point::operator < (const Point& another) {
	return m_x != another.m_x ? m_x < another.m_x : m_y < another.m_y;
}
