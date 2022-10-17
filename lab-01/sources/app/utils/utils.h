#ifndef _UTILS_H_
#define _UTILS_H_
#include <GL/glut.h>

// this file is used to define all of the requirements about drawing

// coding convention:
// - point: integer
// - length or distance: float

#include "../object/Point.h"
#include "../object/Color.h"
#include <vector>

const int WINDOWS_WIDTH = 600;
const int WINDOWS_HEIGHT = 600;

void draw_line_dda(Point, Point, float point_size = 2.0, Color color = Color::BLACK); // code = 0

void draw_line_bresenham(Point, Point, float point_size = 2.0, Color color = Color::BLACK); // code = 1

void draw_circle_midpoint(Point, float, float point_size = 2.0, Color color = Color::BLACK); // code = 2

void draw_elipse_midpoint(Point, float, float, float point_size = 2.0, Color color = Color::BLACK); // code = 3 

void draw_parapole_midpoint(Point, float, float point_size = 2.0, Color color = Color::BLACK); // code = 4

void draw_hyperpole_midpoint(Point, float, float, float point_size = 2.0, Color color = Color::BLACK); // code = 5

//////////////// For easy call
void draw_line_dda_easycall(std::vector<float>, float point_size = 2.0, Color color = Color::BLACK); // code = 0

void draw_line_bresenham_easycall(std::vector<float>, float point_size = 2.0, Color color = Color::BLACK); // code = 1

void draw_circle_midpoint_easycall(std::vector<float>, float point_size = 2.0, Color color = Color::BLACK); // code = 2

void draw_elipse_midpoint_easycall(std::vector<float>, float point_size = 2.0, Color color = Color::BLACK); // code = 3 

void draw_parapole_midpoint_easycall(std::vector<float>, float point_size = 2.0, Color color = Color::BLACK); // code = 4

void draw_hyperpole_midpoint_easycall(std::vector<float>, float point_size = 2.0, Color color = Color::BLACK); // code = 5


void set_pixel(GLint, GLint);

#endif