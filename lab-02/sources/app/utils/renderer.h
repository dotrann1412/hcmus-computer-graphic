#ifndef _RENDERER_H_
#define _RENDERER_H_

#ifdef __linux__ 
#include <GL/glut.h>
#else
#include <gl/glut.h>
#endif

#include <map>
#include <vector>
#include <functional>
#include <string>

#include "../objects/Color.h"
#include "../objects/Point.h"
#include "../objects/Pixel.h"

// this static class is used to avoid global var using 
class Renderer
{
public: // utils function
    static const float ks_point_size;

    static const Color ks_default_color;

    static const int WINDOW_HEIGHT;
    
    static const int WINDOW_WIDTH;

    static void display();

    static int glut_initialize(char** args, int args_count);

    static void draw_line_bresenham(const Point& first, const Point& last, const Color& color, const int& id = 0);

    static void setPixelCallback(const int& x, const int& t, const Pixel& color);

private:
    static std::vector<std::vector<Pixel>> k_color_map;
};

#endif // 