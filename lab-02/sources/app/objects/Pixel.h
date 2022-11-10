#ifndef __PIXEL_H__
#define __PIXEL_H__

#include <cstdint>
#include <vector>

class Pixel
{
public:
	uint8_t m_info[4];

	Pixel(uint8_t info[]);
	Pixel(const std::vector<int8_t>& info);
	Pixel();
	Pixel(const Pixel&);
};

#endif