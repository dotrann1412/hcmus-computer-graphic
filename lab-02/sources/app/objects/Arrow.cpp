#include "Arrow.h"

Arrow::Arrow(const Point& rect_start, const Point& rect_end,  const Color& boundary_colors, const Color& fill_colors)
    : Shape(rect_start, rect_end, boundary_colors, fill_colors)
{

}

Arrow::Arrow(const Arrow& another)
    : Shape(another)
{

}

void Arrow::render() const
{
    glBegin(GL_POINTS);

    glEnd();

    if (m_fillColor != Color::WHITE)
        boundary_fill();
}

bool Arrow::contain(const Point& )
{

}

