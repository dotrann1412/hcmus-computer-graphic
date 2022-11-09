#ifndef _COLOR_H_
#define _COLOR_H_

#ifdef __linux__ 
#include <GL/glut.h>
#else
#include <gl/glut.h>
#endif

#include <iostream>


class Color
{
public:
	uint8_t R, G, B;
	Color() : R(0), G(0), B(0) {};
	Color(uint8_t R, uint8_t G, uint8_t B) : R(R), G(G), B(B) {};
	Color(const Color& another) : R(another.R), G(another.G), B(another.B) {};

	const static Color RED;
	const static Color BLUE;
	const static Color GREEN;
	const static Color BLACK;
	const static Color WHITE;

	bool operator == (const Color& another) const;
	bool operator != (const Color& another) const;

	friend std::ostream &operator << (std::ostream &s, const Color &a) {
		s << a.R << ' ' << a.G << ' ' << a.B;
		return s;
	}
};


#endif // _COLOR_H_