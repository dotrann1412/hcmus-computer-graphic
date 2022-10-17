#include "renderer.h"


const float Renderer::ks_point_size = 2.0;
const Color Renderer::ks_default_color = Color::BLACK;
std::function<void(std::vector<float>, float, Color)> Renderer::k_worker;
std::vector<float> Renderer::k_parameters;

void Renderer::display() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0);

    int x1 = 500, y1 = 5, x2 = 250,  y2 = 250;

    Renderer::k_worker(k_parameters, ks_point_size, ks_default_color);

    glFlush();
}


void Renderer::init(const std::function<void(std::vector<float>, float, Color)>& worker
                  , const std::vector<float>& parameters) 
{
    Renderer::k_worker = worker;
    Renderer::k_parameters = parameters;
}

void Renderer::init(
    const std::pair<
        std::function<void(std::vector<float>, float, Color)>, 
        std::vector<float>>& params
    ) 
{
    Renderer::k_worker = params.first;
    Renderer::k_parameters = params.second;
}