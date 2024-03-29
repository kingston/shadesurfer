// STColor4ub.cpp
#include "STColor4ub.h"

#include "STColor3f.h"
#include "STColor4f.h"
#include "STUtil.h"

/* Helper routine - convert a single component f->ub */
static unsigned char clampComponent(float c)
{
    return (unsigned char) STMax(0.f, STMin(255.f, c * 255.f));
}

/* Constructors */
STColor4ub::STColor4ub()
    : r(0), g(0), b(0), a(0)
{
}

STColor4ub::STColor4ub(const STColor4ub& c)
    : r(c.r), g(c.g), b(c.b), a(c.a)
{
}

STColor4ub::STColor4ub(Component c, Component _a)
    : r(c), g(c), b(c), a(_a)
{
}

STColor4ub::STColor4ub(Component _r, Component _g, Component _b, Component _a)
    : r(_r), g(_g), b(_b), a(_a)
{
}

STColor4ub::STColor4ub(const STColor3f& c, Component _a)
    : r(clampComponent(c.r))
    , g(clampComponent(c.g))
    , b(clampComponent(c.b))
    , a(_a)
{
}

STColor4ub::STColor4ub(const STColor4f& c)
    : r(clampComponent(c.r))
    , g(clampComponent(c.g))
    , b(clampComponent(c.b))
    , a(clampComponent(c.a))
{
}

STColor4ub STColor4ub::operator+(const float s) const
{
    STColor4ub rval;
    rval.r = this->r + s;
    rval.g = this->g + s;
    rval.b = this->b + s;
    rval.a = this->a;
    return rval;
}

STColor4ub STColor4ub::operator-(const float s) const
{
    return *this + (-s);
}

char minc(char lhs, char rhs)
{
    return lhs < rhs ? lhs : rhs;
}

STColor4ub STColor4ub::operator+(const STColor4ub& rhs) const
{
    STColor4ub rval;
    rval.r = minc(255, this->r + rhs.r);
    rval.g = minc(255, this->g + rhs.g);
    rval.b = minc(255, this->b + rhs.b);
    rval.a = this->a;
    return rval;
}

STColor4ub STColor4ub::operator-(const STColor4ub& rhs) const
{
    STColor4ub rval;
    rval.r = this->r - rhs.r;
    rval.g = this->g - rhs.g;
    rval.b = this->b - rhs.b;
    rval.a = this->a;
    return rval;
}

STColor4ub STColor4ub::operator*(const float s) const
{
    STColor4ub rval;
    rval.r = this->r * s;
    rval.g = this->g * s;
    rval.b = this->b * s;
    rval.a = this->a;
    return rval;
}

STColor4ub STColor4ub::operator/(const float s) const
{
    return *this * (1.f / s);
}
