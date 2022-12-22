#ifndef __TORUS_H__
#define __TORUS_H__

#include "Shape3D.h"

class Torus : Shape3D {
public:
	Torus();
	Torus(const Point3i& pos, const std::vector<int>& sides);
	Torus(const Torus& another);

	void render();
	void setMotion(void);
};

#endif // __TORUS_H__