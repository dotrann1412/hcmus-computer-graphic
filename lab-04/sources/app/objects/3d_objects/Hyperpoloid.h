#ifndef __HYPERPOLOID_H__
#define __HYPERPOLOID_H__

#include "Shape3D.h"

class Hyperpoloid : Shape3D {
public:
	Hyperpoloid();
	Hyperpoloid(const Point3i& pos, const std::vector<int>& sides);
	Hyperpoloid(const Hyperpoloid& another);

	void render();
	void setMotion(void);
};

#endif // __HYPERPOLOID_H__