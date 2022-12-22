#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Point.h"
#include "../commons/Color.h"

#ifdef __linux__ 
#include <GL/glut.h>
#else
#include <gl/glut.h>
#endif

#include <functional>

#include <stack>

#include <vector>
#include <cassert>

template<class key_t, class value_t> 
using hashmap = std::unordered_map<key_t, value_t>;

using Transformer = std::vector<std::vector<double>>;

template<class T = double>
struct LinePack {
	std::pair<T, T> first;
	std::pair<T, T> second;
	LinePack(std::pair<T, T> first, std::pair<T, T> second) : first(first), second(second) {}
	LinePack(const LinePack<T>& another) : first(another.first), second(another.second) {};
};

bool inside(const Point& point, const std::vector<Point>& boundary);

class Shape2D
{
public:
	Shape2D(const Point& rect_start, const Point& rect_end, const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);

	Shape2D(const Shape2D& another);

	virtual void render() const = 0;
	
	virtual bool contain(const Point& point);
	
	virtual ~Shape2D();

	virtual Point center() const;

	virtual void boundary_fill() const;

	virtual void switchStatus();

	void setFillColor(const Color& );

	void setBoundaryColor(const Color& );

	Color getFillColor();

	Color getBoundaryColor();

	virtual void setBoundary(const Point& first, const Point& second);

	bool filled();

	void select();
	
	void unselect();

	bool isSelected();

	void transformDefault();

	void shift(int dx, int dy);

	void scale(double ratio);

	void rotate(double alpha);

	void setPixel(int x, int y) const;

protected:
	void bresenham (
		Point first, 
		Point last
	) const;

	void bresenham_rev (
		Point first,
		Point last
	) const;

	virtual void unbound();

protected:

	float m_pointSize;
	
	Transformer m_trans;

	Point m_bottomLeft;

	Point m_topRight;

	Color m_boundaryColor;

	Color m_fillColor;

	uint8_t m_id;

	bool m_isSelected;

public:
	static void initialize(const uint32_t& screen_width, const uint32_t& screen_height);

	static void clear_buffer();

protected:

	static std::stack<uint8_t> k_avalableID;
	
	static bool k_hasInititalized;

	static std::vector<std::vector<uint8_t>> k_borderID;
};

#endif // __SHAPE_H__