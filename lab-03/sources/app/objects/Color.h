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
	unsigned char R, G, B;
	Color() : R(0), G(0), B(0) {};
	
	Color(unsigned char R, unsigned char G, unsigned char B) : R(R), G(G), B(B) {};
	
	Color(const Color& another) : R(another.R), G(another.G), B(another.B) {};

	Color darker();

	Color brighter();

	const static Color RED;
	
	const static Color BLUE;
	
	const static Color GREEN;
	
	const static Color BLACK;
	
	const static Color WHITE;

	const static Color CYAN;

	const static Color YELLOW;

	const static Color PURBLE;

	const static Color GRAY;

	const static Color ORANGE;

	bool operator == (const Color& another) const;
	
	bool operator != (const Color& another) const;

	Color& operator = (const Color& color);

	friend std::ostream &operator << (std::ostream &s, const Color &a) {
		s << (int)a.R << ' ' << (int)a.G << ' ' << (int)a.B;
		return s;
	}
};


#endif // _COLOR_H_