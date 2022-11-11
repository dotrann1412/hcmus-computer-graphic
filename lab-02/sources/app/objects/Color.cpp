#include "Color.h"

#include <cmath>

const Color Color::RED = { 255, 0, 0 };
const Color Color::BLUE = {0, 0, 255};
const Color Color::GREEN = { 0, 255, 0 };
const Color Color::BLACK = { 0, 0, 0 };
const Color Color::WHITE = { 255, 255, 255 };

bool Color::operator == (const Color& another) const {
	return this->R == another.R
		&&  this->G == another.G
		&&  this->B == another.B;
}

Color& Color::operator = (const Color& color) {
	R = color.R;
	G = color.G;
	B = color.B;
	return *this;
}


bool Color::operator != (const Color& another) const {
	return 1 - (*this == another);
}