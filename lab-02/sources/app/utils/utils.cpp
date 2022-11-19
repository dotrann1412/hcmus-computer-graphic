#include "utils.h"
#include "timer.h"

#ifdef __linux__
#include <GL/glut.h>
#else
#include <gl/glut.h>
#endif

#include <cmath>

#include <iostream>

using std::cerr;

bool isInt(const string& s) {
    bool is_negative = s[0] == '-';

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
