#include "utils.h"
#include <GL/glut.h>
#include <cmath>

#include <iostream>

using std::cerr;


void draw_line_dda (Point first, Point last, float point_size, Color color)
{
	cerr << "[*][DDA] Drawing line: " << first << '\t' << last << '\n';
	// code = 1
	glBegin(GL_POINTS);

	// configuration
	glPointSize(point_size);
	glColor3b(color.R, color.G, color.B);

	// code = 0
	// 
	// idea is calculate the slope of the line then step by step calculate y by x
	// - slope = dy / dx

	if (first > last)
		swap(first, last);

	int dx = last.x() - first.x();
	int dy = last.y() - first.y();

	float m = 1.0 * dy / dx;

	if (dx > abs(dy)) {
		float y = first.y();
		for (int x = first.x(); x <= last.x(); ++x, y += m) {
			glVertex2i(x, y);
		}
	}
	else {
		m = abs(1.0 / m);
		int interval = dy < 0 ? -1 : 1;
		float x = first.x();
		for (int y = first.y(); y != last.y() + interval; y += interval, x += m) {
			glVertex2i(x, y);
		}
	}

	glEnd();
}

void draw_line_bresenham(Point first, Point last, float point_size, Color color)
{
	cerr << "[*][BRESENHAM] Drawing line: " << first << '\t' << last << '\n';
	glBegin(GL_POINTS);

	glPointSize(point_size);
	glColor3b(color.R, color.G, color.B);

	if (first > last)
		swap(first, last);
	
	int dx = last.x() - first.x();
	int dy = last.y() - first.y();
	
	bool is_negative_slope = false;
	if (dy < 0) dy = -dy, is_negative_slope = true;

	if (dx > dy) {
		int p = 2 * dy - dx;
		const int A = 2 * dy;
		const int B = 2 * (dy - dx);

		int interval = 1;
		if (is_negative_slope) interval = -1;
		
		for (int x = first.x(), y = first.y(); x <= last.x(); ++x) {
			if (p <= 0) p += A;
			else p += B, y += interval;
			glVertex2i(x, y);
		}
	}
	else {
		int p = 2 * dx - dy;
		const int A = 2 * dx;
		const int B = 2 * (dx - dy);

		int interval = 1;
		if (is_negative_slope) interval = -1;

		for (int x = first.x(), y = first.y(); y != last.y() + interval; y += interval) {
			if (p <= 0) p += A;
			else p += B, ++x;
			glVertex2i(x, y);
		}
	}

	glEnd();
}

void draw_circle_gl(Point center, float r, float point_size, Color color)
{
	
	
}

void draw_circle_midpoint(Point center, float r, float point_size, Color color)
{
	// code = 2
	glBegin(GL_POINTS);

	glPointSize(point_size);
	glColor3b(color.R, color.G, color.B);

	int center_x = center.x(); // move here for faster computing
	int center_y = center.y();

	glVertex2i(center_x, center_y + r);
	glVertex2i(center_x, center_y -r);
	glVertex2i(center_x - r, center_y);
	glVertex2i(center_x + r, center_y);

	int p = 1 - r;
	int x = 1;
	int y = r;

	while (x < y) {
		if (p < 0) p += 2 * x + 3;
		else --y, p += 2 * (x - y) + 3;

		glVertex2i(center_x + x, center_y + y); glVertex2i(center_y + y, center_x + x);
		glVertex2i(center_x + x, center_y - y); glVertex2i(center_y + y, center_x - x);
		glVertex2i(center_x - x, center_y + y); glVertex2i(center_y - y, center_x + x);
		glVertex2i(center_x - x, center_y - y); glVertex2i(center_y - y, center_x - x);

		cerr << x << ' ' << y << '\n';
		++x;
	}

	glEnd();
}

void draw_elipse_gl(Point center, float r, float point_size, Color color)
{

}

void draw_elipse_midpoint(Point center, float rx, float ry, float point_size, Color color)
{
	// code = 3 
	glBegin(GL_POINTS);
	glPointSize(point_size);
	glColor3b(color.R, color.G, color.B);
	int x = 0, y = ry;
	int64_t rx_squared = rx * rx;
	int64_t ry_squared = ry * ry;
	int64_t dx = 2 * ry_squared * x;
	int64_t dy = 2 * rx_squared * y;

	int center_x = center.x();
	int center_y = center.y();

	int64_t d1 = ry_squared - rx_squared * ry + 0.25f * rx_squared;

	while (dx < dy) {
		glVertex2i(center_x + x, center_y + y);
		glVertex2i(center_x + x, center_y - y);
		glVertex2i(center_x - x, center_y + y);
		glVertex2i(center_x - x, center_y - y);
		
		if (d1 < 0) {
			dx += 2ll * ry_squared;
			d1 += dx + ry_squared;
		}
		else {
			--y;
			dx += 2ll *		ry_squared;
			dy -= 2ll * rx_squared;
			d1 += dx - dy + ry_squared;
		}

		++x;
	}

	int64_t d2 = ry_squared * (1.0f * x + 0.5f) * (1.0f * x + 0.5f) + rx_squared * (y - 1) * (y - 1) - rx_squared * ry_squared;
	while (y >= 0) {
		glVertex2i(center_x + x, center_y + y);
		glVertex2i(center_x + x, center_y - y);
		glVertex2i(center_x - x, center_y + y);
		glVertex2i(center_x - x, center_y - y);
		
		if (d2 > 0) {
			dy -= 2ll * rx_squared;
			d2 += rx_squared - dy;
		}
		else {
			++x;
			dx += 2 * ry_squared;
			dy -= 2 * rx_squared;
			d2 += dx - dy + rx_squared;
		}

		--y;
	}

	glEnd();
}

void draw_parapole_gl(Point center, float r, float point_size, Color color)
{

}

void draw_parapole_midpoint(Point center, float p, float point_size, Color color)
{
	glBegin(GL_POINTS);
	glPointSize(point_size);
	glColor3b(color.R, color.G, color.B);
	// code = 4
	
	int x = 0, y = 0;
	int center_x = center.x();
	int center_y = center.y();
	int ip = p, sign = 1;

	if (ip < 0) sign = -1, ip = -ip;
	int d = 1 + 2 * ip;

	while (x <= 2 * ip) {
		glVertex2i(center_x + x, center_y + y * sign);
		glVertex2i(center_x - x, center_y + y * sign);
		if (d < 0) d += 2 * x + 3;
		else ++y, d += 2 * x + 3 - 4 * ip;
		++x;
	}

	d = (2 * ip - 0.5) * (2 * ip - 0.5) - 4 * ip * (ip + 1);
	while (center_y + y * sign < WINDOWS_HEIGHT && center_y + y * sign >= 0) {
		glVertex2i(center_x + x, center_y + y * sign);
		glVertex2i(center_x - x, center_y + y * sign);
		if (d >= 0) d += -4 * ip;
		else d += 2 * x - 4 * ip, ++x;
		++y;
	}

	glEnd();
}

void draw_hyperpole_gl(Point center, float r, float point_size, Color color)
{

}

void draw_hyperpole_midpoint(Point center, float rx, float ry, float point_size, Color color)
{
	// code = 5
	glBegin(GL_POINTS);
	int x = 0, y = ry;
	int64_t rx_squared = rx * rx;
	int64_t ry_squared = ry * ry;
	int64_t dx = 2 * ry_squared * x;
	int64_t dy = 2 * rx_squared * y;

	int center_x = center.x();
	int center_y = center.y();

	int64_t d1 = ry_squared - rx_squared * ry + 0.25f * rx_squared;

	while (dx < dy) {
		glVertex2i(center_x + x, center_y + y);
		glVertex2i(center_x + x, center_y - y);
		glVertex2i(center_x - x, center_y + y);
		glVertex2i(center_x - x, center_y - y);

		if (d1 < 0) {
			dx += 2ll * ry_squared;
			d1 += dx + ry_squared;
		}
		else {
			++y;
			dx += 2ll * ry_squared;
			dy -= 2ll * rx_squared;
			d1 += dx - dy + ry_squared;
		}

		++x;
	}

	int64_t d2 = ry_squared * (1.0f * x + 0.5f) * (1.0f * x + 0.5f) + rx_squared * (y - 1) * (y - 1) - rx_squared * ry_squared;
	while (y < WINDOWS_WIDTH) {
		glVertex2i(center_x + x, center_y + y);
		glVertex2i(center_x + x, center_y - y);
		glVertex2i(center_x - x, center_y + y);
		glVertex2i(center_x - x, center_y - y);

		if (d2 <= 0) {
			dy -= 2ll * rx_squared;
			d2 += rx_squared - dy;
		}
		else {
			++x;
			dx += 2 * ry_squared;
			dy -= 2 * rx_squared;
			d2 += dx - dy + rx_squared;
		}

		++y;
	}
	glEnd();
}

///////////////////////////////////// easycall function //////////////////////////////////////

void draw_line_dda_easycall(std::vector<float> params, float point_size, Color color)
{
	draw_line_dda({params[0], params[1]}, {params[2], params[3]});
} // code = 0

void draw_line_bresenham_easycall(std::vector<float> params, float point_size, Color color)
{
	draw_line_bresenham({params[0], params[1]}, {params[2], params[3]});
} // code = 1

void draw_circle_midpoint_easycall(std::vector<float> params, float point_size, Color color)
{
	draw_circle_midpoint({params[0], params[1]}, params[2]);
} // code = 2

void draw_elipse_midpoint_easycall(std::vector<float> params, float point_size, Color color)
{
	draw_elipse_midpoint({params[0], params[1]}, params[2], params[3]);
} // code = 3 

void draw_parapole_midpoint_easycall(std::vector<float> params, float point_size, Color color)
{
	draw_parapole_midpoint({params[0], params[1]}, params[2]);
} // code = 4

void draw_hyperpole_midpoint_easycall(std::vector<float> params, float point_size, Color color)
{
	draw_elipse_midpoint({params[0], params[1]}, params[2], params[3]);
} // code = 5


void set_pixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}