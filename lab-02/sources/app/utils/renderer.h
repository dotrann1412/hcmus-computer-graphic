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

public: // utils function
    static int glut_initialize(char** args, int args_count);

    static void add_obj(const std::string&);

    static void onResize(int width, int height);
};

#endif // 