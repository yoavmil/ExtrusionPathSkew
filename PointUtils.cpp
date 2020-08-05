#include "PointUtils.h"

Micron vSize2(const Point& p0)
{
    return p0.X * p0.X + p0.Y * p0.Y;
}

double vSize2D(const Point& p0)
{
    return (double)(p0.X * p0.X + p0.Y * p0.Y);
}

float vSize2f(const Point& p0)
{
    return float(p0.X) * float(p0.X) + float(p0.Y) * float(p0.Y);
}

Micron vSize(const Point& p0)
{
    return (int64_t)sqrt(vSize2(p0));
}

double vSizeD(const Point& p0)
{
    return sqrt(vSize2D(p0));
}

Point normal(const Point& p0, double len)
{
    double _len = double(vSize(p0));
    if (_len < 1)
        return Point((Micron)len, 0);
    return p0 * (len / _len);
}

Point normal(const Point& p0, Micron len)
{
    double _len = double(vSizeD(p0));
    if (_len < 1)
        return Point((Micron)len, 0);
    return p0 * ((double)len / _len);
}

Micron dot(const Point& p0, const Point& p1)
{
    return p0.X * p1.X + p0.Y * p1.Y;
}

Micron MicronMin()
{
    return std::numeric_limits<Micron>().min();
}

Micron MicronMax()
{
    return std::numeric_limits<Micron>().max();
}
Micron ToMicron(float mm)
{
    return RoundToUm(mm * MMf_TO_UM);
}
Micron ToMicron(double mm)
{
    return RoundToUm(mm * MMd_TO_UM);
}
Point ToMicron(float x, float y)
{
    return Point(ToMicron(x), ToMicron(y));
}
Micron RoundToUm(double um)
{
	return Micron(std::round(um));
}
Micron RoundToUm(float um)
{
    return Micron(std::round(um));
}
float FloatMin()
{
    return std::numeric_limits<float>().min();
}
float FloatMax()
{
    return std::numeric_limits<float>().max();
}
double DoubleMin()
{
    return std::numeric_limits<double>().min();
}
double DoubleMax()
{
    return std::numeric_limits<double>().max();
}
float ToMm(Micron um)
{
	return um / MMf_TO_UM;
}
Point PointUtils::Rotated(const Point& p, double radian)
{
    Point ret = p;
    return Rotate(ret, radian);
}

Point& PointUtils::Rotate(Point& p, double radian)
{
    double cs = cos(radian), sn = sin(radian);
    p = {
        RoundToUm(p.X * cs - p.Y * sn),
        RoundToUm(p.X * sn - p.Y * cs),
    };
    return p;
}

Point PointUtils::RotatedLeft(const Point& p)
{
    return Point(-p.Y, p.X);
}

Point PointUtils::Lerp(const Point& a, const Point& b, double t)
{
    return a + (b - a) * t;
}

Micron PointUtils::Cross(const Point& a, const Point& b)
{
    return a.X * b.Y - a.Y * b.X;
}

Micron PointUtils::Dot(const Point& p0, const Point& p1)
{
    return p0.X * p1.X + p0.Y * p1.Y;
}

double PointUtils::Angle(const Point& p)
{
    return atan2(p.Y, p.X);
}

double PointUtils::Angle(const Point& p0, const Point& p1)
{   // https://stackoverflow.com/a/16544330/2378218
    Micron dot = PointUtils::Dot(p0, p1);
    Micron det = PointUtils::Cross(p0, p1);
    return atan2(det, dot);
}

double PointUtils::TurnAngle(const Point& a, const Point& b, const Point& c)
{
    return Angle(b - a, c - b);
}

Point PointUtils::Normal(const Point& p0, double len)
{
    double _len = vSizeD(p0);
    if (_len < 1)
        return Point(0, 0);
    return p0 * (len / _len);
}

Point PointUtils::Normal(const Point& p0, Micron len)
{
    double _len = vSizeD(p0);
    if (_len < 1)
        return Point(0, 0);
    return p0 * ((double)len / _len);
}

Point PointUtils::ClosestPointOnLine(const Point& point, const Point& a, const Point& b)
{ // https://stackoverflow.com/a/3122532/2378218

    if (a == b) return a;
    auto aToPoint = point - a;
    auto aToB = b - a;
    auto dist2 = vSize2(aToB);
    auto aToPoint_dot_aTob = Dot(aToPoint, aToB); // projection of a->point on a->b
    double t = (double)aToPoint_dot_aTob / (double)dist2; // magnitude of projection

    if (t < 0) return a;
    if (t > 1) return b;
    return a + aToB * t;
}

Micron PointUtils::Distance(const Point& p0, const Point& p1)
{
	return RoundToUm(sqrt(Distance2(p0, p1)));
}

Micron PointUtils::Distance2(const Point& p0, const Point& p1)
{
    const Point diff = p0 - p1;
    return Size2(diff);

}

Micron PointUtils::Size(const Point& p)
{
    return RoundToUm(sqrt(Size2(p)));
}

Micron PointUtils::Size2(const Point& p)
{
    return p.X * p.X + p.Y * p.Y;
}
