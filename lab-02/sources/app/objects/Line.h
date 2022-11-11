#ifndef LINE_H
#define LINE_H

#include <cmath>
#include <string>

#include "Point.h"



#include "Shape.h"

class Line: public Shape
{
private:
	Point m_start, m_end;

public:
	//constructors
	Line();

	Line(const Point&, const Point& );
	
	Line(const Line&); //copy structor
	
	~Line();

public:
	void render() const;
	bool contain(const Point& point);
	void unbound();

public:
	//return euclid distance between starting and ending point
	float length() const;

	std::string to_string() const;

	Point getStartingPoint() const;

	Point getEndingPoint() const;

	void setStartingPoint(Point);

	void setEndingPoint(Point);

};

#endif