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

const int Renderer::WINDOW_WIDTH = 500;

const int Renderer::WINDOW_HEIGHT = 500;

const float Renderer::ks_point_size = 1.0;

const Color Renderer::ks_default_color = Color::BLACK;

std::vector<std::function<void(std::vector<float>)>> Renderer::k_workers;

std::vector<std::vector<float>> Renderer::k_parameters;

const std::map<int, std::function<void(std::vector<float>)>> Renderer::function_mapping = {

};

const std::map<int, std::string> Renderer::window_title_mapping = {

};

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
    return id;
}

void Renderer::onResize(int w, int h) {
    std::cerr << "[WINDOWS]\t" << "Reshape" << '\n';
    // glutReshapeWindow(Renderer::WINDOW_WIDTH, Renderer::WINDOW_HEIGHT);
}