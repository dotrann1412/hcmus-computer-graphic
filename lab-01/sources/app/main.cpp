#include <GL/glut.h>
#include <iostream>

#include "app_handler.h"
#include "utils/utils.h"
#include "utils/renderer.h"

using namespace std;

// this function should be removed after everything complete
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0);

    int x1 = 500, y1 = 5, x2 = 250,  y2 = 250;
    // line(Point(x1, y1), Point(x2, y2), 3);
    // draw_line_dda(Point(x1, y1), Point(x2, y2), 10, Color::GREEN);
    // draw_line_bresenham(Point(x1 - 10, y1), Point(x2 - 10, y2), 10, Color::GREEN);
    // draw_circle_midpoint({ 100, 100 }, 70);

    // draw_elipse_midpoint({ 100, 100 }, 100, 30);
    GLUquadricObj* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_SILHOUETTE);
    gluDisk(quad, 0.0, 100, 64, 100);
    gluDeleteQuadric(quad);

    // draw_hyperpole_midpoint({ 100, 100 }, 100, 30);
    glFlush();
}

int main(int argc, char** argv)
{
    glut_initialize(argv, argc);

    std::pair<std::function<void(std::vector<float>, float, Color)>, std::vector<float>> 
        params = parse_requirements(argv, argc);

    Renderer::init(params.first, params.second);

    glutDisplayFunc(Renderer::display);

    glutMainLoop();
    return 0;
}