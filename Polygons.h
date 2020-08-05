#ifndef UTILS_POLYGON_H
#define UTILS_POLYGON_H

#include <vector>

using std::vector;
#include "clipper.hpp"
#include "PointUtils.h"

typedef ClipperLib::Path Polygon;

// a wrapper for ClipperLibs polygons
class Polygons : public ClipperLib::Paths
{
public:
    // c'tors
    Polygons() = default;
    Polygons(const Polygons& other) = default;
    Polygons(const Polygon& poly) { this->push_back(poly); }

    void skew(Micron factor, Micron window);
    Polygons addSamplePoints(Micron minDistance) const;

    static Point GetPointFrom(const Polygon& polygon, Micron dist, size_t i, bool* tooShort = nullptr); // dist could be negative too
    static void AddSamplePoints(Polygons& polys, Micron minDistance);
    static void AddSamplePoints(Polygon& poly, Micron minDistance);
    static void Skew(Polygon& poly, Micron factor, Micron window); // each vertex moves by turn radian * factor
};

#endif//UTILS_POLYGON_H
