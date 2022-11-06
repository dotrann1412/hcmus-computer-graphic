#if _MSC_VER && !__INTEL_COMPILER
#pragma warning (disable : 26451)
#endif // turn off integer overflow warning while devleoped in visual studio

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

const int Renderer::WINDOW_WIDTH = 1000;

const int Renderer::WINDOW_HEIGHT = 1000;

const float Renderer::ks_point_size = 2.0;

const Color Renderer::ks_default_color = Color::BLACK;

std::vector<std::function<void(std::vector<float>)>> Renderer::k_workers;

std::vector<std::vector<float>> Renderer::k_parameters;

const std::map<int, std::function<void(std::vector<float>)>> Renderer::function_mapping = {
    {-1, Renderer::draw_line_opengl_easycall},
    {0, Renderer::draw_line_dda_easycall},
    {1, Renderer::draw_line_bresenham_easycall},
    {2, Renderer::draw_circle_midpoint_easycall},
    {3, Renderer::draw_elipse_midpoint_easycall},
    {4, Renderer::draw_parapole_midpoint_easycall},
    {5, Renderer::draw_hyperpole_midpoint_easycall},
};

const std::map<int, std::string> Renderer::window_title_mapping = {
    {-1, "draw_line_opengl_easycall"},
    {0, "draw_line_dda_easycall"},
    {1, "draw_line_bresenham_easycall"},
    {2, "draw_circle_midpoint_easycall"},
    {3, "draw_elipse_midpoint_easycall"},
    {4, "draw_parapole_midpoint_easycall"},
    {5, "draw_hyperpole_midpoint_easycall"},
};

#include "../objects/all.h"

void Renderer::display() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0);

    static std::vector<std::shared_ptr<Shape>> shape_vector = {
        std::shared_ptr<Rectangle>(new Rectangle({100, 100}, {500, 300})),
        std::shared_ptr<Circle>(new Circle({100, 100}, {300, 300})),
        std::shared_ptr<Square>(new Square({100, 200}, {300, 500})),
        std::shared_ptr<Elipse>(new Elipse({200, 300}, {900, 700})),
        std::shared_ptr<Line>(new Line({100, 500}, {900, 100})),
        std::shared_ptr<Triangle>(new Triangle({100, 600}, {950, 50}))
    };

    for (auto x: shape_vector) {
        x->render();
    }

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
        
        if (!Path::exists(filepath) || !Path::isFile(filepath)) {
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
    // this is an algorithm that uses floating point for calculating
    // because the slope of line is constant
    // --> use it to cumulative calculating
    // read the report.pdf for more details.

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

void Renderer::draw_line_opengl(Point first, Point last)
{
    // code = -1
    
    glBegin(GL_LINES);
        glVertex2f(first.x(), first.y());
        glVertex2f(last.x(), last.y());
    glEnd();
}

void Renderer::draw_line_bresenham(Point first, Point last)
{
    // this algorithm just uses integers for all the calculating processed.
    // read the report.pdf for more details.

    if (first > last)
        swap(first, last);
    
    int dx = last.x() - first.x();
    int dy = last.y() - first.y();
    
    bool is_negative_slope = false;
    if (dy < 0) dy = -dy, is_negative_slope = true;

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
    // like bresenham, midpoint is an algorithm that use dynamic programming and integer only!
    // In one step we choose the x[i+1], y[i+1]
    // estimated that calculations on floating point take time 
    //      more than 2 or 3 times compared with calculating on integer
    // --> this is a high performance algorithm
    // read the report.pdf for more details.

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

        glVertex2i(center_x + x, center_y + y); 
        glVertex2i(center_y + y, center_x + x);
        glVertex2i(center_x + x, center_y - y); 
        glVertex2i(center_y + y, center_x - x);
        glVertex2i(center_x - x, center_y + y); 
        glVertex2i(center_y - y, center_x + x);
        glVertex2i(center_x - x, center_y - y); 
        glVertex2i(center_y - y, center_x - x);

        ++x;
    }

    glEnd();
}

void Renderer::draw_elipse_midpoint(Point center, float rx, float ry)
{
    // like bresenham, midpoint is an algorithm that use dynamic programming and integer only!
    // estimated that calculations on floating point take time 
    //      more than 2 or 3 times in compared with calculation on integer
    // --> this is a high performance algorithm
    // read the report.pdf for more details.

    // code = 3 
    glBegin(GL_POINTS);
    
    int x = 0, y = ry;
    int64_t rx_squared = rx * rx;
    int64_t ry_squared = ry * ry;
    int64_t dx = 2ll * ry_squared * x;
    int64_t dy = 2ll * rx_squared * y;

    int center_x = center.x();
    int center_y = center.y();

    int64_t p1 = ry_squared - rx_squared * ry + 0.25f * rx_squared;

    while (dx < dy) {
        glVertex2i(center_x + x, center_y + y);
        glVertex2i(center_x + x, center_y - y);
        glVertex2i(center_x - x, center_y + y);
        glVertex2i(center_x - x, center_y - y);
        
        if (p1 < 0) {
            dx += 2ll * ry_squared;
            p1 += dx + ry_squared;
        }
        else {
            --y;
            dx += 2ll * ry_squared;
            dy -= 2ll * rx_squared;
            p1 += dx - dy + ry_squared;
        }

        ++x;
    }

    int64_t p2 = ry_squared * (1.0f * x + 0.5f) * (1.0f * x + 0.5f) + rx_squared * (y - 1) * (y - 1) - rx_squared * ry_squared;
    while (y >= 0) {
        glVertex2i(center_x + x, center_y + y);
        glVertex2i(center_x + x, center_y - y);
        glVertex2i(center_x - x, center_y + y);
        glVertex2i(center_x - x, center_y - y);
        
        if (p2 > 0) {
            dy -= 2ll * rx_squared;
            p2 += rx_squared - dy;
        }
        else {
            ++x;
            dx += 2 * ry_squared;
            dy -= 2 * rx_squared;
            p2 += dx - dy + rx_squared;
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
    int d = 1 - 2 * ip; 

    while (x <= 2 * ip) {
        glVertex2i(center_x + x, center_y + y * sign);
        glVertex2i(center_x - x, center_y + y * sign);
        if (d < 0) d += 2 * x + 3;
        else ++y, d += 2 * x + 3 - 4 * ip;
        ++x;
    }

    d = (2 * ip - 0.5) * (2 * ip - 0.5) - 4 * ip * (ip + 1);
    
    int limit_width = WINDOW_WIDTH - center_x;
    int limit_height = WINDOW_HEIGHT - center_y;

    if (sign == 1) {
        while (y < limit_height && (x < limit_width || center_x >= x)) {
            glVertex2i(center_x + x, center_y + y);
            glVertex2i(center_x - x, center_y + y);
            if (d >= 0) d += -4 * ip;
            else d += 2 * x - 4 * ip, ++x;
            ++y;
        }
    }
    else {
        while (center_y >= y && (x < limit_width || center_x >= x)) {
            glVertex2i(center_x + x, center_y - y);
            glVertex2i(center_x - x, center_y - y);
            if (d >= 0) d += -4 * ip;
            else d += 2 * x - 4 * ip, ++x;
            ++y;
        }
    }
    glEnd();
}

void Renderer::draw_hyperpole_midpoint(Point center, float a, float b)
{
    // code = 5
    glBegin(GL_POINTS);
    
    int ia = a, ib = b;
    int64_t  b_squared = ib * ib, a_squared = ia * ia;

    int x = ia, y = 0;

    int64_t p = b_squared * ia - 3.0 * b_squared / 4;
    int64_t dx = 2ll * b_squared * ia;
    int64_t dy = 0;

    int center_x = center.x(), center_y = center.y();

    glVertex2i(center_x + x, center_y);
    glVertex2i(center_x - x, center_y);

    int limit_width = WINDOW_WIDTH - center_x;
    int limit_height = WINDOW_HEIGHT - center_y;

    while (dx > dy && x < limit_width) {
        ++y; dy += 2ll * a_squared;
        if (p >= 0) {
            p -= dy + a_squared;
        } else {
            ++x;
            dx += 2ll * b_squared;
            p -= dy + a_squared - dx;
        }

        glVertex2i(center_x + x, center_y + y);
        glVertex2i(center_x + x, center_y - y);
        glVertex2i(center_x - x, center_y + y);
        glVertex2i(center_x - x, center_y - y);
    }

    int64_t q = b_squared * (x + 1) * (x + 1) 
        - a_squared * (1.0 * y + 0.5) * (1.0 * y + 0.5) - a_squared * b_squared;

    while ((x <= center_x || x < limit_width) && (y <= center_y || y < limit_height)) {
        ++x;
        dx += 2ll * b_squared;
        if (q < 0) {
            q += b_squared + dx;
        } else {
            ++y;
            dy += 2ll * a_squared;
            q += b_squared + dx - dy;
        }

        glVertex2i(center_x + x, center_y + y);
        glVertex2i(center_x + x, center_y - y);
        glVertex2i(center_x - x, center_y + y);
        glVertex2i(center_x - x, center_y - y);
    }
 
    glEnd();
}

///////////////////////////////////// easycall function //////////////////////////////////////

void Renderer::draw_line_opengl_easycall(std::vector<float> params)
{
    cout << "[*][LINE][OPENGL] Input: " << params << endl;

    if (params.size() != 4) {
        cout << "[ERROR] draw_line_dda method takes 4 argument found " << params.size() << endl;
        return;
    }

    Timer timer;
    glLineWidth(3.0);
    timer.start();
    draw_line_opengl({ params[0], params[1] }, { params[2], params[3] });
    cout << "\t--> Time executed: " << timer.stop() * 1000 << " (ms)" << endl;
} // code = 0


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
        cout << "[ERROR] draw_circle_midpoint method takes 3 argument found " << params.size() << endl;
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
        cout << "[ERROR] draw_parapole_midpoint method takes 3 argument found " << params.size() << endl;
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

int Renderer::glut_initialize(char** args, int agrs_count) {
    glutInit(&agrs_count, args);
    glutInitWindowSize(Renderer::WINDOW_WIDTH / 2, Renderer::WINDOW_HEIGHT / 2);
    int id = glutCreateWindow("Student 20120057 - Lab 02");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, Renderer::WINDOW_WIDTH, 0.0, Renderer::WINDOW_HEIGHT);
    return id;
}