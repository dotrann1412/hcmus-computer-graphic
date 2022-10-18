#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <GL/glut.h>
#include <map>
#include <vector>
#include <functional>
#include "../object/Color.h"

// this static class is used to avoid global var using 
class Renderer
{
private:
    static std::function<void(std::vector<float>, float, Color)> k_worker;
    static std::vector<float> k_parameters;
    static const float ks_point_size;
    static const Color ks_default_color;

public:
    static void init(const std::function<void(std::vector<float>, float, Color)>& worker
                    , const std::vector<float>& parameters);

    static void init(const std::pair<std::function<void(std::vector<float>, float, Color)>, std::vector<float>>&);

    static void display();
};

#endif // 