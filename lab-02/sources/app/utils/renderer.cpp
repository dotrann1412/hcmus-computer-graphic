#pragma warning (disable : 26451)

#include "renderer.h"
#include "path.h"

#include "utils.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "timer.h"

#include <memory>

using std::string;
using std::cout;
using std::fstream;

const int Renderer::WINDOW_WIDTH = 500;

const int Renderer::WINDOW_HEIGHT = 500;

const float Renderer::ks_point_size = 1.0;

const Color Renderer::ks_default_color = Color::BLACK;

std::vector<std::vector<Pixel>> Renderer::k_color_map;

#include "../objects/all.h"
void Renderer::display() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ui(255, 0, 0);
    glPointSize(3.0);

    static std::vector<std::shared_ptr<Shape>> shape_vector = {
        // std::shared_ptr<Circle>(new Circle({100, 100}, {300, 300})),
        std::shared_ptr<Rectangle>(new Rectangle({400, 100}, {450, 450})),
        // std::shared_ptr<Elipse>(new Elipse({100, 0}, {400, 200}))
    };

    std::cerr << "Rendering..." << '\n';
    for (auto x: shape_vector) {
        x->render();
    }

    static std::vector<Color> colors = {Color::BLACK, Color::GREEN, Color::RED};

    for (auto x: shape_vector) {
        x->fill(Color::GREEN);
    }


    glFlush();
}


void set_pixel(GLint x, GLint y)
{
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

int Renderer::glut_initialize(char** args, int agrs_count) {
    glutInit(&agrs_count, args);
    glutInitWindowSize(Renderer::WINDOW_WIDTH, Renderer::WINDOW_HEIGHT);
    int id = glutCreateWindow("Student 20120057 - Lab 02");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, Renderer::WINDOW_WIDTH, 0.0, Renderer::WINDOW_HEIGHT);
    k_color_map.assign(Renderer::WINDOW_WIDTH, std::vector<Pixel>(Renderer::WINDOW_WIDTH));
    return id;
}

void Renderer::draw_line_bresenham(const Point& first, const Point& last, const Color& color, const int& id)
{
    // this algorithm just uses integers for all the calculating processed.
    // read the report.pdf for more details.

    if (first > last)
        swap(first, last);
    
    int dx = last.x() - first.x();
    int dy = last.y() - first.y();
    
    bool is_negative_slope = false;
    if (dy < 0) dy = -dy, is_negative_slope = true;

    Pixel pix = {color.R, color.G, color.B, id};

    glBegin(GL_POINTS);
    
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
            k_color_map[x][y] = pix;
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
            k_color_map[x][y] = pix;
        }
    }

    glEnd();
    glFlush();
}

void Renderer::setPixelCallback(const int& x, const int& y, const Pixel& pixel)
{
    k_color_map[x][y] = pixel;
}

void Renderer::push(const int& x, const int& y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}