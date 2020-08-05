
#ifndef points_h__
#define points_h__

#include "clipper.hpp"

typedef ClipperLib::IntPoint Point;
typedef ClipperLib::cInt Micron;
Micron MicronMin();
Micron MicronMax();
Micron ToMicron(float mm);
Micron ToMicron(double mm);
Point ToMicron(float x, float y);
Micron RoundToUm(double um);
Micron RoundToUm(float um);
float FloatMin();
float FloatMax();
double DoubleMin();
double DoubleMax();
float ToMm(Micron um);
constexpr float MMf_TO_UM = 1000.f;
constexpr double MMd_TO_UM = 1000.;

/* Extra operators to make it easier to do math with the 64bit Point objects */
inline Point operator+(const Point& p0, const Point& p1) { return Point(p0.X + p1.X, p0.Y + p1.Y); }
inline Point operator-(const Point& p0, const Point& p1) { return Point(p0.X - p1.X, p0.Y - p1.Y); }
inline Point operator*(const Point& p0, const double i) { return Point(RoundToUm(p0.X * i), RoundToUm(p0.Y * i)); }
inline Point operator*(double i, const Point& p) { return  p * i; }
inline Point operator*(const Point& p0, const Micron i) { return Point(p0.X * i, p0.Y * i); }
inline Point operator*(Micron i, const Point& p) { return  p * i; }
inline Point operator/(const Point& p0, const int64_t i) { return Point(p0.X / i, p0.Y / i); }
inline void operator-=(Point& p0, const Point& p1) { p0 = p0 - p1; }
inline void operator+=(Point& p0, const Point& p1) { p0 = p0 + p1; }
inline Point operator-(const Point& p0) { return Point(-p0.X, -p0.Y); }

// TODO move those to class PointUtils
Micron vSize2(const Point& p0);
double vSize2D(const Point& p0);
float vSize2f(const Point& p0);
Micron vSize(const Point& p0);
double vSizeD(const Point& p0);
Point normal(const Point& p0, double len);
Point normal(const Point& p0, Micron len);
Micron dot(const Point& p0, const Point& p1);

class PointUtils {
public:
    static Point Rotated(const Point& p, double radian);
    static Point& Rotate(Point& p, double radian);
    static Point RotatedLeft(const Point& p);
    static Point Lerp(const Point& a, const Point& b, double t /*[0,1]*/);
    static Micron Cross(const Point& a, const Point& b);
    static Micron Dot(const Point& p0, const Point& p1);
    static double Angle(const Point& p);
    static double Angle(const Point& p0, const Point& p1); // [-PI, PI]
    static double TurnAngle(const Point& a, const Point& b, const Point& c); // [-PI, PI], the turn angle from AB to BC
    static Point Normal(const Point& p0, double len);
    static Point Normal(const Point& p0, Micron len);
    static Point ClosestPointOnLine(const Point& point, const Point& a, const Point& b);
    static Micron Distance(const Point& p0, const Point& p1);
    static Micron Distance2(const Point& p0, const Point& p1);
    static Micron Size(const Point& p);
    static Micron Size2(const Point& p);
};

#endif // points_h__

