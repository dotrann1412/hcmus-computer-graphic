#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <string>
#include <string.h>
#include <sstream>

using namespace std;

class Point
{
private:
	//x_pos and y_pos
	float m_x, m_y;
	//i dont think declare this attribute as public attribute
	//what about if user do: Point::objCount = 1000000 ?
	//->not safe
	static int k_obj_count;
public:
	//constructors
	Point();
	Point(const float&, const float&);
	Point(const Point&);

	//destructor
	~Point();

public:
	//getter
	float x() const;
	float y() const;

public:
	//setter
	void setx(const float&);
	void sety(const float&);

public:
	//return distance between 2 pts
	float distance(const Point&) const;
	static float distance(const Point&, const Point&);
	
public:
	//toString and getInstanceCount
	std::string to_string() const; //return information of this string under a string
	static int instance_count(); //return the number of Point initialized

	friend std::istream& operator >> (std::istream& s, Point&);
	friend std::ostream& operator << (std::ostream& s, const Point&);

	bool operator > (const Point& another);
	bool operator < (const Point& another);

public:
	static Point* parse(std::string);
	static Point* try_parse(std::string);
};

#endif