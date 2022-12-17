#ifndef __SHAPE_H__
#define __SHAPE_H__

class Shape
{
public:
	Shape();
	Shape(const Shape&);
	virutal ~Shape();

public:
	virtual void render() = 0;
	virtual void setMotion(void) = 0;

private:
	
};

#endif