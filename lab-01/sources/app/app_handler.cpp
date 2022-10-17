#include "app_handler.h"
#include "./utils/timer.h"

#include <iostream>
#include <string>

using std::string;
using std::vector;
using std::cout;
using std::cerr;

void glut_initialize(char** args, int agrs_count) {
    glutInit(&agrs_count, args);
    glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
    glutCreateWindow("Student 20120057");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOWS_WIDTH, 0.0, WINDOWS_HEIGHT);
}

bool isInt(const string& s) {
    bool is_negative = false;

    if (!s.size())
        return false;
    
    if (is_negative && s.size() == 1)
        return false;
    
    for (int i = is_negative; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }

    return true;
}

bool isFloat(const string& s) {
    bool is_negative = false,
         floating_point_detected = false;
    if (!s.size())
        return false;
    
    is_negative = s[0] == '-';
    if (is_negative && s.size() == 1)
        return false;

    if (s.size() > 1 && is_negative && s[1] == '.')
        return false;
    
    for (int i = is_negative; i < s.size(); ++i) {
        if (s[i] == '.') {
            if (floating_point_detected) return false;
            floating_point_detected = true;
        } else if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    
    return true;
}

bool validate(const vector<string>& args) {
    for (int i = 2; i < args.size(); ++i) {
        cerr << "[DEBUG]: " << args[i] << '\n';
        if (!isFloat(args[i]))
            return false;
    }

    if (args.size() == 1)
        return false;
    
    return isInt(args[1]);
}

void help() {

}

std::pair<int, vector<float>> parameters(vector<string> args) {
    if (!validate(args)) {
        return {0, {0, 0, 300, 300}};
        // throw "Parameters failed on parsing!";
    };

    vector<float> params(args.size() - 2);
    for (int i = 2; i < args.size(); ++i) {
        params[i - 2] = stof(args[i]);
    }

    return {stoi(args[1]), params};
}

std::pair<std::function<void(std::vector<float>, float, Color)>, vector<float>> parse_requirements(char** args, int args_count)
{
    vector<string> args_vec(args_count);
    for (int i = 0; i < args_count; ++i)
        args_vec[i] = string(args[i]);
    
    auto params = parameters(args_vec);
    std::function<void(std::vector<float>, float, Color)> renderer = function_mapping.find(params.first)->second;

    return {renderer, params.second};
}