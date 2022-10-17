#ifndef _APP_HANDLER_H_
#define _APP_HANDLER_H_

#include <map>
#include <functional>
#include <vector>
#include "./utils/utils.h"

// this file is used to implement all of requirement of app flow and case exception

typedef void (*display_ptr) (void);

std::pair<std::function<void(std::vector<float>, float, Color)>, vector<float>> parse_requirements(char** args, int args_count);

void glut_initialize(char** args, int args_count);

const static std::map<int, std::function<void(std::vector<float>, float, Color)>> function_mapping = {
    {0, draw_line_dda_easycall},
    {1, draw_line_bresenham_easycall},
    {2, draw_circle_midpoint_easycall},
    {3, draw_elipse_midpoint_easycall},
    {4, draw_parapole_midpoint_easycall},
    {5, draw_hyperpole_midpoint_easycall},
};


#endif // _APP_HANDLER_H_