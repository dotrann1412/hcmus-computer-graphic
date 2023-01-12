#ifndef __CONE_H__
#define __CONE_H__

#include "Shape3D.h"

class Cone : public Shape3D {
public:
	Cone();
	Cone(const Point3i& pos, const std::vector<int>& sides, const int& texture);
	Cone(const Cone& another);

	void render();
	void setMotion(void);

private:
	static const int KS_NUMC, KS_NUMT;
};

#endif // __CONE_H__