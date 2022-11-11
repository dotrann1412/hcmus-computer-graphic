#include "Shape.h"

#include "cmath"

#include <functional>
#include <iostream>
#include <queue>

Shape::Shape(const Point& rect_start, const Point& rect_end, const Color& boundary_colr, const Color& fill_color) {
	m_bottomLeft = {std::min(rect_start.x(), rect_end.x()), std::min(rect_start.y(), rect_end.y())};
	m_topRight = {std::max(rect_start.x(), rect_end.x()), std::max(rect_start.y(), rect_end.y())};
	m_boundaryColor = boundary_colr;
    m_fillColor = fill_color;
    do {
        m_id = rand() % 256;
    } while (k_idMarker.find(m_id) != k_idMarker.end());
    k_idMarker[m_id] = true;
}

Shape::Shape(const Shape& another) {
	m_bottomLeft = another.m_bottomLeft;
	m_topRight = another.m_topRight;
	m_boundaryColor = another.m_boundaryColor;
    m_fillColor = another.m_fillColor;
}

Shape::~Shape() {
    k_idMarker.erase(m_id);
}

bool Shape::contain(const Point& point) {
	return point.x() >= m_bottomLeft.x() && point.x() <= m_topRight.x() 
		&& point.y() >= m_bottomLeft.y() && point.y() <= m_topRight.y();
}

void Shape::boundary_fill() const {
	static int dx[] = {1, -1, 0, 0};
	static int dy[] = {0, 0, 1, -1};
    
    Point t_center = center();
    std::queue<std::pair<int, int>> que;
    
    struct Pack {
        int R, G, B;
        Pack(int _R, int _G, int _B): R(_R), G(_G), B(_B) {}
        Pack(): R(255), G(255), B(255) {}
        bool operator != (Pack another) {
            return !(*this == another);
        }

        bool operator == (Pack another) {
            return R == another.R && G == another.G && B == another.B;
        }
    };

    int frame_width = m_topRight.x() + 1 - m_bottomLeft.x();
    int frame_height = m_topRight.y() + 1 - m_bottomLeft.y();
    
    int x_offset = m_bottomLeft.x();
    int y_offset = m_bottomLeft.y();

    std::vector<std::vector<Pack>> color_map(frame_width, std::vector<Pack>(frame_height)); 

    Pack boundary_color = {m_fillColor.R, m_fillColor.G, m_fillColor.B},
        boundary = {m_boundaryColor.R, m_boundaryColor.G, m_boundaryColor.B};

    glColor3ub(m_fillColor.R, m_fillColor.G, m_fillColor.B);
    glBegin(GL_POINTS);
    glVertex2i(t_center.x(), t_center.y());
    color_map[t_center.x() - x_offset][t_center.y() - y_offset] = boundary_color;

    que.push({t_center.x(), t_center.y()});

    while (!que.empty()) {
        auto cur = que.front();
        que.pop();
        for (int i = 0; i < 4; ++i) {
            int xx = cur.first + dx[i];
            int yy = cur.second + dy[i];
            
            if (xx - x_offset < 0 || xx - x_offset >= frame_width || yy - y_offset < 0 || yy - y_offset >= frame_height) {
                continue;
            }

            if (color_map[xx - x_offset][yy - y_offset] != boundary_color && k_borderID[xx][yy] != m_id) {
                que.push({xx, yy});
                glVertex2i(xx, yy);
                color_map[xx - x_offset][yy - y_offset] = boundary_color;
            }
        }
    }

    glEnd();
    glFlush();
}

void Shape::bresenham(Point first, Point last) const
{
	if (first > last)
        swap(first, last);
    
    int dx = last.x() - first.x();
    int dy = last.y() - first.y();
    
    bool is_negative_slope = false;
    if (dy < 0) dy = -dy, is_negative_slope = true;


    glBegin(GL_POINTS);
    glPointSize(2.0);
    glColor3ub(m_boundaryColor.R, m_boundaryColor.G, m_boundaryColor.B);

    if (dx > dy) {
        int p = 2 * dy - dx;
        const int A = 2 * dy;
        const int B = 2 * (dy - dx);

        int interval = 1;
        if (is_negative_slope) interval = -1;
        
        for (int x = first.x(), y = first.y(); x <= last.x(); ++x) {
            glVertex2i(x, y);
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
            glVertex2i(x, y);
            k_borderID[x][y] = m_id;
            if (p <= 0) p += A;
            else p += B, ++x;
        }
    }

	glEnd();
}

Point Shape::center() const {
	return {(m_bottomLeft.x() + m_topRight.x()) / 2, (m_bottomLeft.y() + m_topRight.y()) / 2};
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

hashmap<uint8_t, bool> Shape::k_idMarker;
std::vector<std::vector<uint8_t>> Shape::k_borderID;