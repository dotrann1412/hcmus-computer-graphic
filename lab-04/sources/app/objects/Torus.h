#ifndef __TORUS_H__
#define __TORUS_H__

#include "Shape3D.h"

class Torus : public Shape3D {
public:
	Torus();
	Torus(const Point3i& pos, const std::vector<int>& sides, const int& texture);
	Torus(const Torus& another);

	void render();
	void setMotion(void);

private:
	const static int KS_NUMC, KS_NUMT;
};

#endif // __TORUS_H__