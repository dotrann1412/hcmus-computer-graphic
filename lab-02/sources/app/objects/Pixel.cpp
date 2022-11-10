#include "Pixel.h"
#include <cstring>

Pixel::Pixel(uint8_t info[])
{
	for (int i = 0; i < 4; ++i)
		m_info[i] = info[i];
}

Pixel::Pixel(const std::vector<uint8_t>& info)
{
	for (int i = 0; i < 4; ++i)
		m_info[i] = info[i];
}

Pixel::Pixel()
{
	for (int i = 0; i < 4; ++i)
		m_info[i] = 0;
}

Pixel::Pixel(const Pixel& another)
{
	for (int i = 0; i < 4; ++i)
		m_info[i] = another.m_info[i];
}
