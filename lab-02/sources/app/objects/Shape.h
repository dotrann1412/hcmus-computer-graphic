#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Point.h"
#include "Color.h"

#ifdef __linux__ 
#include <GL/glut.h>
#else
#include <gl/glut.h>
#endif

#include <functional>

#include <unordered_map>

#include <vector>

template<class key_t, class value_t> 
using hashmap = std::unordered_map<key_t, value_t>;

class Shape
{
public:
	Shape(const Point& rect_start, const Point& rect_end, const Color& boundary_color = Color::BLACK, const Color& fill_color = Color::WHITE);

	Shape(const Shape& another);

	virtual void render() const = 0;
	
	virtual bool contain(const Point& point);
	
	virtual ~Shape();

	virtual Point center() const;

	virtual void boundary_fill() const;

	virtual void switchStatus();

	void setFillColor(const Color& );

	void setBoundaryColor(const Color& );

	Color getFillColor();

	Color getBoundaryColor();

	virtual void setBoundary(const Point& first, const Point& second);

	bool filled();

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

	Point m_bottomLeft;

	Point m_topRight;

	Color m_boundaryColor;

	Color m_fillColor;

	uint8_t m_id;

	bool m_isSelecting;

public:
	static void initialize(const uint32_t& screen_width, const uint32_t& screen_height);

	static void clear_buffer();

protected:

	static hashmap<uint8_t, bool> k_idMarker;

	static std::vector<std::vector<uint8_t>> k_borderID;
};

#endif // __SHAPE_H__