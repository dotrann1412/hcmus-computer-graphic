#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include "Shape3D.h"

class Cylinder : public Shape3D {
public:
	Cylinder();
	Cylinder(const Point3i& pos, const std::vector<int>& sides, const int& texture);
	Cylinder(const Cylinder& another);

	void render();
	void setMotion(void);
};

#endif // __CYLINDER_H__