#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef __linux__
#include <GL/glut.h>
#else
#include <gl/glut.h>
#endif

// this file is used to define all of the requirements about drawing

// coding convention:
// - point: integer
// - length or distance: float

#include "../objects/Point.h"
#include "../objects/Color.h"
#include <vector>

bool isInt(const string& s);
bool isFloat(const string& s);

/////// quick io
template <class T> 
std::istream &operator >> (std::istream &s, std::vector<T> &a) {
	for(T &x: a) s >> x;
	return s;
}

template <class T> 
std::ostream &operator << (std::ostream &s, const std::vector<T> &a) {
	for(const T &x: a) s << x << ' ';
	return s;
}

#endif