#ifndef __POINT3I_H__
#define __POINT3I_H__

#include <cmath>

class Point3i {
private:
    float mx, my, mz;

public:
    Point3i(): mx(0), my(0), mz(0) {}
    Point3i(float x, float y, float z): mx(x), my(y), mz(z) {}
    Point3i(const Point3i& another): mx(another.mx), my(another.my), mz(another.mz) {}

    float x() { return mx; }
    float y() { return my; }
    float z() { return mz; }

    void set(float x, float y, float z) {
        mx = x, my = y, mz = z;
    }

    static float diff(const Point3i& f, const Point3i& s) {
        float diffx = f.mx - s.mx, diffy = f.my - s.my, diffz = f.mz - s.mz;
        return sqrt(diffx * diffx + diffy * diffy + diffz  * diffz);
    }
    
    float diff(const Point3i& another) {
        return Point3i::diff(*this, another);
    }
};

#endif // __POINT3I_H__