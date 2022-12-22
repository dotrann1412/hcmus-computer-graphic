#ifndef __CUBE_H__
#define __CUBE_H__

#include "Shape3D.h"

class Cube : public Shape3D {
public:
	Cube();
	Cube(const Point3i& pos, const std::vector<int>& sides);
	Cube(const Cube& another);

	void render();
	void setMotion(void);
};

#endif // __CUBE_H__