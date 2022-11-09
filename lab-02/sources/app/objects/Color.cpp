#include "Color.h"

#include <cmath>

const Color Color::RED = { 255, 0, 0 };
const Color Color::BLUE = {0, 0, 255};
const Color Color::GREEN = { 0, 255, 0 };
const Color Color::BLACK = { 0, 0, 0 };
const Color Color::WHITE = { 255, 255, 255 };

bool Color::operator == (const Color& another) const {
	return (1 << 8) * this->R == int(1 << 8) * another.R
		&& (1 << 8) * this->G == int(1 << 8) * another.G
		&& (1 << 8) * this->B == int(1 << 8) * another.B;
}

bool Color::operator != (const Color& another) const {
	return 1 - (*this == another);
}