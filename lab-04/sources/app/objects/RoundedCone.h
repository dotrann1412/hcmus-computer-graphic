#ifndef __ROUNDED_CONE_H__
#define __ROUNDED_CONE_H__

#include "Shape3D.h"

class RoundedCone : public Shape3D {
public:
	RoundedCone();
	RoundedCone(const Point3i& pos, const std::vector<int>& sides, const int& texture);
	RoundedCone(const RoundedCone& another);

	void render();
	void setMotion(void);

private:
	static const int KS_NUMC, KS_NUMT;
};

#endif // __ROUNDED_CONE_H__