#include "renderer.h"
#include "path.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "timer.h"

using std::string;
using std::cout;
using std::fstream;

const int Renderer::WINDOW_WIDTH = 1000;

const int Renderer::WINDOW_HEIGHT = 1000;

const float Renderer::ks_point_size = 2.0;

const Color Renderer::ks_default_color = Color::BLACK;

std::vector<std::function<void(std::vector<float>)>> Renderer::k_workers;

std::vector<std::vector<float>> Renderer::k_parameters;

const std::map<int, std::function<void(std::vector<float>)>> Renderer::function_mapping = {
    {0, Renderer::draw_line_dda_easycall},
    {1, Renderer::draw_line_bresenham_easycall},
    {2, Renderer::draw_circle_midpoint_easycall},
    {3, Renderer::draw_elipse_midpoint_easycall},
    {4, Renderer::draw_parapole_midpoint_easycall},
    {5, Renderer::draw_hyperpole_midpoint_easycall},
};

const std::map<int, std::string> Renderer::window_title_mapping = {
    {0, "draw_line_dda_easycall"},
    {1, "draw_line_bresenham_easycall"},
    {2, "draw_circle_midpoint_easycall"},
    {3, "draw_elipse_midpoint_easycall"},
    {4, "draw_parapole_midpoint_easycall"},
    {5, "draw_hyperpole_midpoint_easycall"},
};


void Renderer::display() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0);

    for (int i = 0; i < k_workers.size(); ++i)
        k_workers[i](k_parameters[i]);

    glFlush();
}

void Renderer::add_obj(const std::string& line)
{
    stringstream ss(line);
    int code = 0;
    ss >> code;

    auto iter = Renderer::function_mapping.find(code);        
    if (iter != Renderer::function_mapping.end()) {
        vector<float> params;
        
        for (float x; ss >> x
            ; params.push_back(x));
        
        k_workers.push_back(iter->second);
        k_parameters.push_back(params);
    }
}

void Renderer::render(char** args, int argcnt) 
{
    // run with files
    if (argcnt > 2 && string(args[1]) == "-f") {
        string filepath = args[2];
        if (!Path::exists(filepath) or !Path::isFile(filepath)) {
            cout << "[*][ERROR] Program is running with wrong format of parameters, try again!" << '\n';
            return;
        }

        fstream ff(filepath, std::ios::in);
        
        for (std::string buffer; getline(ff, buffer)
            ; Renderer::add_obj(buffer));
    }
    else {
         // run with parameters
        bool valid = true;
        for (int i = 2; i < argcnt && valid
            ; valid = isFloat(args[i++]));

        valid = valid && argcnt >= 2 && isInt(args[1]);

        if (!valid) {
            cout << "[*][ERROR] Program is running with wrong format of parameters, try again!" << '\n';
            return;
        }

        int code = stoi(args[1]);
        vector<float> params(argcnt - 2);
        for (int i = 0; i < argcnt - 2; ++i) {
            params[i] = stof(args[i + 2]);
        }

        auto iter = function_mapping.find(code);
        if (iter != function_mapping.end()) {
            k_workers.push_back(iter->second);
            k_parameters.push_back(params);
        }
    }

    glut_initialize(args, argcnt);
    glutDisplayFunc(Renderer::display);
    glutMainLoop();
}


void Renderer::draw_line_dda (Point first, Point last)
{
    // code = 1
    glBegin(GL_POINTS);

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

void Renderer::draw_line_bresenham(Point first, Point last)
{
    glBegin(GL_POINTS);


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

void Renderer::draw_circle_midpoint(Point center, float r)
{
    // code = 2
    glBegin(GL_POINTS);

    

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

        ++x;
    }

    glEnd();
}

void Renderer::draw_elipse_midpoint(Point center, float rx, float ry)
{
    // code = 3 
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
            --y;
            dx += 2ll *     ry_squared;
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

void Renderer::draw_parapole_midpoint(Point center, float p)
{
    glBegin(GL_POINTS);
    
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
    
    if (sign == 1) {
        while (center_y + y < WINDOW_HEIGHT) {
            glVertex2i(center_x + x, center_y + y);
            glVertex2i(center_x - x, center_y + y);
            if (d >= 0) d += -4 * ip;
            else d += 2 * x - 4 * ip, ++x;
            ++y;
        }
    }
    else {
        while (center_y - y >= 0) {
            glVertex2i(center_x + x, center_y - y);
            glVertex2i(center_x - x, center_y - y);
            if (d >= 0) d += -4 * ip;
            else d += 2 * x - 4 * ip, ++x;
            ++y;
        }
    }
    glEnd();
}

void Renderer::draw_hyperpole_midpoint(Point center, float rx, float ry)
{
    // code = 5
    glBegin(GL_POINTS);
    
    
    int irx = rx;
    int iry = ry;

    int64_t rx_squared = irx * irx;
    int64_t ry_squared = iry * iry;

    int center_x = center.x();
    int center_y = center.y();

    int64_t p = ry_squared * (1.0 * irx - 0.5) * (1.0 * irx - 0.5) - rx_squared - rx_squared * ry_squared;

    glVertex2i(center_x, center_y + irx);
    glVertex2i(center_x, center_y - irx);

    int x = 1, y = irx;
    while (center_y + y < WINDOW_HEIGHT || center_y - y >= 0) {
        
        glVertex2i(center_x + x, center_y + y);
        glVertex2i(center_x + x, center_y - y);
        glVertex2i(center_x - x, center_y + y);
        glVertex2i(center_x - x, center_y - y);

        if (p >= 0) p -= rx_squared * (2ll * x + 3);
        else p += 2ll * ry_squared * y - rx_squared * (2ll * x + 3), ++y;
        ++x;
    }

    glEnd();
}

///////////////////////////////////// easycall function //////////////////////////////////////

void Renderer::draw_line_dda_easycall(std::vector<float> params)
{
    cout << "[*][LINE][DDA] Input: " << params << endl;
    
    if (params.size() != 4) {
        cout << "[ERROR] draw_line_dda method takes 4 argument found " << params.size() << endl;
        return;
    }

    Timer timer;
    timer.start();
    draw_line_dda({params[0], params[1]}, {params[2], params[3]});
    cout << "\t--> Time executed: " << timer.stop() * 1000 << " (ms)" << endl;
} // code = 0

void Renderer::draw_line_bresenham_easycall(std::vector<float> params)
{
    cout << "[*][LINE][BRESENHAM] Input: " << params << endl;
    if (params.size() != 4) {
        cout << "[ERROR] draw_line_dda method takes 4 argument found " << params.size() << endl;
        return;
    }

    Timer timer;
    timer.start();
    draw_line_bresenham({params[0], params[1]}, {params[2], params[3]});
    cout << "\t--> Time executed: " << timer.stop() * 1000 << " (ms)" << endl;
} // code = 1

void Renderer::draw_circle_midpoint_easycall(std::vector<float> params)
{
    cout << "[*][CIRCLE][MIDPOINT] Input: " << params << endl;
    if (params.size() != 3) {
        cout << "[ERROR] draw_circle_midpoint method takes 4 argument found " << params.size() << endl;
        return;
    }
    
    Timer timer;
    timer.start();
    draw_circle_midpoint({params[0], params[1]}, params[2]);
    cout << "\t--> Time executed: " << timer.stop() * 1000 << " (ms)" << endl;
} // code = 2

void Renderer::draw_elipse_midpoint_easycall(std::vector<float> params)
{
    cout << "[*][ELIPSE][MIDPOINT] Input: " << params << endl;
    if (params.size() != 4) {
        cout << "[ERROR] draw_elipse_midpoint method takes 4 argument found " << params.size() << endl;        
        return;
    }
    
    Timer timer;
    timer.start();
    draw_elipse_midpoint({params[0], params[1]}, params[2], params[3]);
    cout << "\t--> Time executed: " << timer.stop() * 1000 << " (ms)" << endl;
} // code = 3 

void Renderer::draw_parapole_midpoint_easycall(std::vector<float> params)
{
    cout << "[*][PARABOLE][MIDPOINT] Input: " << params << endl;
    if (params.size() != 3) {
        cout << "[ERROR] draw_parapole_midpoint method takes 4 argument found " << params.size() << endl;
        return;
    }
    
    Timer timer;
    timer.start();
    draw_parapole_midpoint({params[0], params[1]}, params[2]);
    cout << "\t--> Time executed: " << timer.stop() * 1000 << " (ms)" << endl;
} // code = 4

void Renderer::draw_hyperpole_midpoint_easycall(std::vector<float> params)
{
    cout << "[*][HYPERBOLE][MIDPOINT] Input: " << params << endl;
    if (params.size() != 4) {
        cout << "[ERROR] draw_hyperpole_midpoint method takes 4 argument found " << params.size() << endl;
        return;
    }
    
    Timer timer;
    timer.start();
    draw_hyperpole_midpoint({params[0], params[1]}, params[2], params[3]);
    cout << "\t--> Time executed: " << timer.stop() * 1000 << " (ms)" << endl;
} // code = 5

void set_pixel(GLint x, GLint y)
{
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

void Renderer::glut_initialize(char** args, int agrs_count) {
    glutInit(&agrs_count, args);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Student 20120057 - Lab 01");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

