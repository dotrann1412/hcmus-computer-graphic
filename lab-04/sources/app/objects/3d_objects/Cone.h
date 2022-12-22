#ifndef __CONE_H__
#define __CONE_H__

#include "Shape3D.h"

class Cone : Shape3D {
public:
	Cone();
	Cone(const Point3i& pos, const std::vector<int>& sides);
	Cone(const Cone& another);

	void render();
	void setMotion(void);
};

#endif // __CONE_H__