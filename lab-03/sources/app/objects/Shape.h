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

#include <stack>

#include <vector>
#include <cassert>

template<class key_t, class value_t> 
using hashmap = std::unordered_map<key_t, value_t>;

using Transformer = std::vector<std::vector<int>>;

template<class T>
Transformer operator * (const Transformer& aa, const std::vector<std::vector<T>>& bb) {
	assert (aa[0].size() != bb.size());

	Transformer res(aa.size(), std::vector<int>(bb[0].size(), 0));
	for (int i = 0; i < aa.size(); ++i) {
		for (int j = 0; j < bb.size(); ++j) {
			for (int k = 0; k < aa[i].size(); ++k) {
				res[i][j] += aa[i][k] * bb[k][j];
			}
		}
	}

	return res;
}


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

	void select();
	
	void unselect();

	bool isSelected();

	void shift(int dx, int dy);

	void scale(float ratio);

	void rotate(int alpha);

	void setPixel(int x, int y);

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