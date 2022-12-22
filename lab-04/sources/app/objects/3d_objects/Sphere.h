#ifndef __PHERE_H__
#define __PHERE_H__

#include "Shape3D.h"

class Sphere : public Shape3D {
public:
	Sphere();
	Sphere(const Point3i& pos, const std::vector<int>& sides);
	Sphere(const Sphere& another);

	~Sphere();

	void render();
	void setMotion(void);

private:
	static const int STACK_COUNT;
	static const int SECTOR_COUNT;
};

#endif // __PHERE_H__