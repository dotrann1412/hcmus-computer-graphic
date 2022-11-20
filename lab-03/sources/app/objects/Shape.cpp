#include "Shape.h"

#include "cmath"

#include <functional>
#include <iostream>
#include <queue>

template<class T>
std::vector<std::vector<T>> operator * (const std::vector<std::vector<T>>& aa, const std::vector<std::vector<T>>& bb) {
    assert(aa[0].size() == bb.size());

    std::vector<std::vector<T>> res(aa.size(), std::vector<double>(bb[0].size(), 0));
    for (int i = 0; i < aa.size(); ++i) {
        for (int j = 0; j < bb.size(); ++j) {
            for (int k = 0; k < aa[i].size(); ++k) {
                res[i][j] += aa[i][k] * bb[k][j];
            }
        }
    }

    return res;
}

Shape::Shape(const Point& rect_start, const Point& rect_end, const Color& boundary_colr, const Color& fill_color) {
    if (!k_hasInititalized) {
        for (int i = 0; i < 1 << 8; ++i) {
            k_avalableID.push(i);
        }
        k_hasInititalized = true;
    }

	m_bottomLeft = {std::min(rect_start.x(), rect_end.x()), std::min(rect_start.y(), rect_end.y())};
	m_topRight = {std::max(rect_start.x(), rect_end.x()), std::max(rect_start.y(), rect_end.y())};
	m_boundaryColor = boundary_colr;
    m_fillColor = fill_color;
    m_id = 0;
    m_pointSize = 1.7;

    m_trans = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    if (!k_avalableID.empty()) {
        m_id = k_avalableID.top();
        k_avalableID.pop();
    }
    else {
        cout << "[WARNING] ID manager ran out of resource. Erase any drawn object to continue normally." << '\n';
    }

    m_isSelected = false;
}

Shape::Shape(const Shape& another) {
	m_bottomLeft = another.m_bottomLeft;
	m_topRight = another.m_topRight;
	m_boundaryColor = another.m_boundaryColor;
    m_fillColor = another.m_fillColor;
    m_trans = another.m_trans;
    m_pointSize = another.m_pointSize;

    if (!k_avalableID.empty()) {
        m_id = k_avalableID.top();
        k_avalableID.pop();
    }
    else {
        cout << "[WARNING] ID manager ran out of resource. Erase any drawn object to continue normally." << '\n';
    }
}

Shape::~Shape() {
    unbound();
    k_avalableID.push(m_id);
}

bool Shape::contain(const Point& point) {
    std::vector<Point> boundary = {
        m_bottomLeft,
        {m_bottomLeft.x(), m_topRight.y()},
        m_topRight,
        {m_topRight.x(), m_bottomLeft.y()}
    };

    for (auto& x: boundary)
        x = x.transform(m_trans);

    return inside(point, boundary);
}

void Shape::boundary_fill() const {
	static int dx[] = {1, -1, 0, 0};
	static int dy[] = {0, 0, 1, -1};
    
    Point t_center = center();
    int x_offset = m_bottomLeft.x();
    int y_offset = m_bottomLeft.y();

    if (k_borderID[t_center.x()][t_center.y()] == m_id)
        return;

    std::queue<std::pair<int, int>> que;

    int frame_width = m_topRight.x() + 1 - m_bottomLeft.x();
    int frame_height = m_topRight.y() + 1 - m_bottomLeft.y();
    
    std::vector<std::vector<uint8_t>> color_map(frame_width, std::vector<uint8_t>(frame_height, 0)); 

    glColor3ub(m_fillColor.R, m_fillColor.G, m_fillColor.B);
    glBegin(GL_POINTS);
    setPixel(t_center.x(), t_center.y());

    color_map[t_center.x() - x_offset][t_center.y() - y_offset] = 1;
    que.push({t_center.x(), t_center.y()});

    while (!que.empty()) {
        auto cur = que.front();
        que.pop();

        for (int i = 0; i < 4; ++i) {
            int xx = cur.first + dx[i];
            int yy = cur.second + dy[i];
            
            if (xx < x_offset || xx - x_offset >= frame_width || yy < y_offset || yy - y_offset >= frame_height) {
                continue;
            }

            if (!color_map[xx - x_offset][yy - y_offset] && k_borderID[xx][yy] != m_id) {
                que.push({xx, yy});
                setPixel(xx, yy);
                color_map[xx - x_offset][yy - y_offset] = 1;
            }
        }
    }

    glEnd();
}

void Shape::bresenham(Point first, Point last) const
{
	if (first > last)
        swap(first, last);
    
    int dx = last.x() - first.x();
    int dy = last.y() - first.y();
    
    bool is_negative_slope = false;
    if (dy < 0) dy = -dy, is_negative_slope = true;

    glColor3ub(m_boundaryColor.R, m_boundaryColor.G, m_boundaryColor.B);
    glBegin(GL_POINTS);

    setPixel(first.x(), first.y());
    setPixel(last.x(), last.y());

    k_borderID[first.x()][first.y()] = k_borderID[last.x()][last.y()] = m_id;

    if (dx > dy) {
        int p = 2 * dy - dx;
        const int A = 2 * dy;
        const int B = 2 * (dy - dx);

        int interval = 1;
        if (is_negative_slope) interval = -1;
        
        for (int x = first.x(), y = first.y(); x <= last.x(); ++x) {
            setPixel(x, y);
            k_borderID[x][y] = m_id;
            if (p <= 0) p += A;
            else p += B, y += interval;
        }
    }
    else {
        int p = 2 * dx - dy;
        const int A = 2 * dx;
        const int B = 2 * (dx - dy);

        int interval = 1;
        if (is_negative_slope) interval = -1;

        for (int x = first.x(), y = first.y(); y != last.y() + interval; y += interval) {
            setPixel(x, y);
            k_borderID[x][y] = m_id;
            if (p <= 0) p += A;
            else p += B, ++x;
        }
    }

	glEnd();
}


void Shape::bresenham_rev(Point first, Point last) const
{
	if (first > last)
        swap(first, last);
    
    int dx = last.x() - first.x();
    int dy = last.y() - first.y();
    
    bool is_negative_slope = false;
    if (dy < 0) dy = -dy, is_negative_slope = true;

    k_borderID[first.x()][first.y()] = k_borderID[last.x()][last.y()] = 0;

    if (dx > dy) {
        int p = 2 * dy - dx;
        const int A = 2 * dy;
        const int B = 2 * (dy - dx);

        int interval = 1;
        if (is_negative_slope) interval = -1;
        
        for (int x = first.x(), y = first.y(); x <= last.x(); ++x) {
            k_borderID[x][y] = 0;
            if (p <= 0) p += A;
            else p += B, y += interval;
        }
    }
    else {
        int p = 2 * dx - dy;
        const int A = 2 * dx;
        const int B = 2 * (dx - dy);

        int interval = 1;
        if (is_negative_slope) interval = -1;

        for (int x = first.x(), y = first.y(); y != last.y() + interval; y += interval) {
            k_borderID[x][y] = 0;
            if (p <= 0) p += A;
            else p += B, ++x;
        }
    }
}

void Shape::unbound() {
    
}

bool Shape::filled() {
    return m_fillColor != Color::WHITE;
}


Point Shape::center() const {
	return {
        (m_bottomLeft.x() + m_topRight.x()) / 2, 
        (m_bottomLeft.y() + m_topRight.y()) / 2
    };
}

void Shape::initialize(const uint32_t& screen_width, const uint32_t& screen_height) {
    k_borderID.assign(screen_width, std::vector<uint8_t>(screen_height, 0));
}

void Shape::clear_buffer() {
    for (auto& x: k_borderID) {
        for (auto& y: x) y = 0;
    }
}

void Shape::switchStatus() {

}


void Shape::setFillColor(const Color& color)
{
    m_fillColor = color;
}

void Shape::setBoundaryColor(const Color& color)
{
    m_boundaryColor = color;
}

Color Shape::getFillColor()
{
    return m_fillColor;
}

Color Shape::getBoundaryColor()
{
    return m_boundaryColor;
}

void Shape::setBoundary(const Point& first, const Point& second) {
    unbound();
    m_bottomLeft = {min(first.x(), second.x()), min(first.y(), second.y())};
    m_topRight = {max(first.x(), second.x()), max(first.y(), second.y())};
}

void Shape::select() {
    if (!m_isSelected)
        m_fillColor = m_fillColor.darker(), m_isSelected = true;
}

void Shape::unselect() {
    if (m_isSelected)
        m_fillColor = m_fillColor.brighter(), m_isSelected = false;
}

void Shape::transformDefault() {
    m_trans = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
    m_pointSize = 1.7;
}

bool Shape::isSelected() {
    return m_isSelected;
}

void Shape::shift(int dx, int dy) {
    m_trans = m_trans * std::vector<std::vector<double>>({{1, 0, 0}, {0, 1, 0}, {1.0 * dx, 1.0 * dy, 1}});
}

void Shape::scale(double ratio) {
    Point _center = center().transform(m_trans);
    Shape::shift(-_center.x(), -_center.y());
    m_trans = m_trans * std::vector<std::vector<double>>({{ratio, 0, 0}, {0, ratio, 0}, {0, 0, 1}});
    Shape::shift( _center.x(),  _center.y());
    m_pointSize *= ratio * ratio;
}

void Shape::rotate(double alpha) {
    Point _center = center().transform(m_trans);
    Shape::shift(-_center.x(), -_center.y());
    m_trans = m_trans * std::vector<std::vector<double>>({{cos(alpha), -sin(alpha), 0}, {sin(alpha), cos(alpha), 0}, {0, 0, 1}});
    Shape::shift( _center.x(),  _center.y());
}

void Shape::setPixel(int x, int y) const {
    glVertex2i(m_trans[0][0] * x + m_trans[1][0] * y + m_trans[2][0], m_trans[0][1] * x + m_trans[1][1] * y + m_trans[2][1]);
}

bool inside(const Point& point, const std::vector<Point>& boundary) {
    auto inLine = [](const Point& lf, const Point& ls, const Point& p) {
        return p.x() <= min(lf.x(), ls.x())
            && p.y() <= min(lf.y(), ls.y());
    };

    auto direction = [](const Point& a, const Point& b, const Point& c) {
        int val = (b.y() - a.y()) * (c.x() - b.x()) - (b.x() - a.x()) * (c.y() - b.y());
        if (!val) return 0;
        if (val < 0) return 2;
        return 1;
    };

    auto intersect = [&direction, &inLine](const Point& l1x, const Point& l1y, const Point& l2x, const Point& l2y) {

        int d1 = direction(l1x, l1y, l2x);
        int d2 = direction(l1x, l1y, l2y);
        int d3 = direction(l2x, l2y, l1x);
        int d4 = direction(l2x, l2y, l1y);

        if (d1 != d2 && d3 != d4)
            return true;

        if (d1 == 0 && inLine(l1x, l1y, l2x))
            return true;

        if (d2 == 0 && inLine(l1x, l1y, l2y))
            return true;

        if (d3 == 0 && inLine(l2x, l2y, l1x))
            return true;

        if (d4 == 0 && inLine(l2x, l2y, l1y))
            return true;

        return false;
    };

    int count = 0;
    Point endingPoint = {9999, point.y()};
    for (int i = 0, n = boundary.size(); i < boundary.size(); ++i) {
        if (intersect(point, endingPoint, boundary[i], boundary[(i + 1) % n])) {
            if (direction(boundary[i], point, boundary[(i + 1) % n]) == 0)
                return inLine(boundary[i], boundary[(i + 1) % n], point);
            ++count;
        }
    }
    return count & 1;
}

std::stack <uint8_t> Shape::k_avalableID;
std::vector<std::vector<uint8_t>> Shape::k_borderID;
bool Shape::k_hasInititalized = false;