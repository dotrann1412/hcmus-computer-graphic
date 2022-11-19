
#include "./helpers.h"

bool inside (const Point& point, const std::vector<Line>& boundary) {
	auto inLine = [] (const Line& l1, const Point& p) {
		return p.x() <= min(l1.getStartingPoint().x(), l1.getEndingPoint().x())
		&& p.y() <= min(l1.getStartingPoint().y(), l1.getEndingPoint().y());
	};

	auto direction = [] (const Point& a, const Point& b, const Point& c) {
		int val = (b.y() - a.y()) * (c.x() - b.x()) - (b.x() - a.x()) * (c.y() - b.y());
        if (!val) return 0 ;
        if  (val < 0) return 2;
        return 1;
    };

	auto intersect = [&direction, &inLine] (const Line& l1, const Line& l2) {
        
        int d1 = direction(l1.getStartingPoint(), l1.getEndingPoint(), l2.getStartingPoint());
        int d2 = direction(l1.getStartingPoint(), l1.getEndingPoint(), l2.getEndingPoint());
        int d3 = direction(l2.getStartingPoint(), l2.getEndingPoint(), l1.getStartingPoint());
        int d4 = direction(l2.getStartingPoint(), l2.getEndingPoint(), l1.getEndingPoint());
        
        if (d1 != d2 && d3 != d4)
            return true;
        
        if (d1 == 0 && inLine(l1, l2.getStartingPoint()))
            return true;
 
        if (d2 == 0 && inLine(l1, l2.getEndingPoint()))
            return true;
    
        if (d3 == 0 && inLine(l2, l1.getStartingPoint()))
            return true;
    
        if (d4 == 0 && inLine(l2, l1.getEndingPoint()))
            return true;
    
        return false;
    };

    int count = 0;
    Line magic = { point, {9999, point.y()} };
    for (int i = 0; i < boundary.size(); ++i) {
        if (intersect(magic, boundary[i])) {
            if (direction(boundary[i].getStartingPoint(), point, boundary[i].getEndingPoint()) == 0)
                return inLine(boundary[i], point);
            ++count;
        }
    }
    return count & 1;
}