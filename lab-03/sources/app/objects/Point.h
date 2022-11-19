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
	int32_t m_x, m_y;
	//i dont think declare this attribute as public attribute
	//what about if user do: Point::objCount = 1000000 ?
	//->not safe
	static int k_obj_count;
public:
	//constructors
	Point();
	Point(const int32_t&, const int32_t&);
	Point(const Point&);

	//destructor
	~Point();

public:
	//getter
	int32_t x() const;
	int32_t y() const;

public:
	//setter
	void setx(const int32_t&);
	void sety(const int32_t&);

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
};

#endif