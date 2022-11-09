#ifndef __ARROW_H__
#define __ARROW_H__

#include "Shape.h"

class Arrow: public Shape
{
public:
	Arrow();
	Arrow(const Arrow& another);
	void render();
	bool contain(const Point& );
};

#endif // __ARROW_H__