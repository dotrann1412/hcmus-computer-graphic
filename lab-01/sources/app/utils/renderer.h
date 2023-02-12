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

// this static class is used to avoid global var using 
class Renderer
{
private:
    static std::vector<std::function<void(std::vector<float>)>> k_workers;

    static std::vector<std::vector<float>> k_parameters;

    static const std::map<int, std::function<void(std::vector<float>)>> function_mapping;

    static const std::map<int, std::string> window_title_mapping;

    static const float ks_point_size;

    static const Color ks_default_color;

    static const int WINDOW_HEIGHT;
    
    static const int WINDOW_WIDTH;

public:
    static void render(char**, int);

    static void display();

public: // algorithms
    
    static void draw_line_dda(Point, Point); // code = 0

    static void draw_line_bresenham(Point, Point); // code = 1

    static void draw_circle_midpoint(Point, float); // code = 2

    static void draw_elipse_midpoint(Point, float, float); // code = 3 

    static void draw_parapole_midpoint(Point, float); // code = 4

    static void draw_hyperpole_midpoint(Point, float, float); // code = 5

    static void draw_line_opengl(Point, Point); // code = -1

public: // easy call

    static void draw_line_dda_easycall(std::vector<float>); // code = 0

    static void draw_line_bresenham_easycall(std::vector<float>); // code = 1

    static void draw_circle_midpoint_easycall(std::vector<float>); // code = 2

    static void draw_elipse_midpoint_easycall(std::vector<float>); // code = 3 

    static void draw_parapole_midpoint_easycall(std::vector<float>); // code = 4

    static void draw_hyperpole_midpoint_easycall(std::vector<float>); // code = 5

    static void draw_line_opengl_easycall(std::vector<float>); // code = -1 

public: // utils function
    static void glut_initialize(char** args, int args_count);

    static void add_obj(const std::string&);
};

#endif // 