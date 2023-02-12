#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
	float R, G, B;
	Color() : R(0), G(0), B(0) {};
	Color(float R, float G, float B) : R(R), G(G), B(B) {};
	Color(const Color& another) : R(another.R), G(another.G), B(another.B) {};

	const static Color RED;
	const static Color BLUE;
	const static Color GREEN;
	const static Color BLACK;
	const static Color WHITE;
};


#endif // _COLOR_H_