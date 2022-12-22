#include "Sphere.h"

const int Sphere::SECTOR_COUNT = 16;
const int Sphere::STACK_COUNT = 16;

Sphere::Sphere() : Shape3D() {

}

Sphere::Sphere(const Point3i& pos, const std::vector<int>& sides) 
: Shape3D(pos, sides) {
	int m = min(xSide, min(ySide, zSide));
}

Sphere::Sphere(const Sphere& another) 
: Shape3D(another) {

}

Sphere::~Sphere() {

}


void Sphere::render() 
{
	glLoadIdentity();

	Point3i pts = center();
	glTranslatef(pts.x(), pts.y(), pts.z());
	
	float xy;

	float radius = 0.5 * min(xSide, min(ySide, zSide));

	static float sectorStep = 2.0 * PI / Sphere::SECTOR_COUNT;
	static float stackStep = PI / Sphere::STACK_COUNT;
	
	float sectorAngle, stackAngle;
	
	glBegin(GL_TRIANGLES);

	static std::vector<int> state = { 0, 1 };
	
	auto process = [&] (int ii, int jj) {
		stackAngle = PI / 2 - ii * stackStep;
		xy = radius * cosf(stackAngle);
		sectorAngle = jj * sectorStep;
		return setPixel(xy * cosf(sectorAngle), xy * sinf(sectorAngle), radius * sinf(stackAngle));
	};

	Point3i p;
	for (int i = 0; i < STACK_COUNT; ++i) {
		for (int j = 0; j < SECTOR_COUNT; ++j) {
			glColor3ub(255, 128, 128);
			process(i, j);
			process(i, (j + 1) % SECTOR_COUNT);
			process((i + 1) % STACK_COUNT, j);

			glColor3ub(128, 255, 128);
			process(i, (j + 1) % SECTOR_COUNT);
			process((i + 1) % STACK_COUNT, j);
			process((i + 1) % STACK_COUNT, (j + 1) % SECTOR_COUNT);
		}
	}

	glEnd();
}

void Sphere::setMotion(void) 
{

}