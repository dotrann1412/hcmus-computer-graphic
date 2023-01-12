#ifndef __HYPERPOLOID_H__
#define __HYPERPOLOID_H__

#include "Shape3D.h"

class Hyperpoloid : public Shape3D {
public:
	Hyperpoloid();
	Hyperpoloid(const Point3i& pos, const std::vector<int>& sides, const int& texture);
	Hyperpoloid(const Hyperpoloid& another);

	void render();
	void setMotion(void);

private:
	const static int KS_NUMC, KS_NUMT;
	const static float KS_ANGLE;
	const static float KS_A, KS_B, KS_C;
};

#endif // __HYPERPOLOID_H__