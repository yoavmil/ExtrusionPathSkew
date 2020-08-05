#include "Polygons.h"

void Polygons::skew(Micron factor, Micron window)
{
	for (auto& poly : *this)
		Skew(poly, factor, window);
}

Polygons Polygons::addSamplePoints(Micron minDistance) const
{
	Polygons polys = *this;
	AddSamplePoints(polys, minDistance);
	return polys;
}

Point Polygons::GetPointFrom(const Polygon& polygon, Micron dist, size_t i, bool* tooShort)
{
	if (polygon.size() == 0) {
		if (tooShort) *tooShort = true;
		return { 0, 0 };
	}

	Micron len = 0;
	size_t sz = polygon.size();
	bool forward = dist > 0;
	int dir = forward ? 1 : -1;
	dist = std::abs(dist);
	if (forward) i++;
	else i = (i + sz - 1) % sz;
	for (size_t j = 0; j < sz && len < dist; j++) {
		const Point& prev = polygon[(i + (dir * j) + sz - (1 * dir)) % sz];
		const Point& curr = polygon[(i + (dir * j) + sz) % sz];
		auto segLength = vSize(curr - prev);
		if (len + segLength < dist) {
			len += segLength;
			continue;
		}
		if (len + segLength == dist) {
			if (tooShort) *tooShort = false;
			return curr;
		}
		Point point = prev + normal(curr - prev, (dist - len));
		if (tooShort) *tooShort = false;
		return point;
	}

	if (tooShort) *tooShort = true;
	return polygon[(i + sz) % sz];
}

void Polygons::AddSamplePoints(Polygons& polys, Micron minDistance)
{
	for (auto& poly : polys) AddSamplePoints(poly, minDistance);
}

void Polygons::AddSamplePoints(Polygon& poly, Micron minDistance)
{
	if (minDistance <= 0)
		throw std::invalid_argument("AddSamplePoints: delta cannot be <= 0");
	Micron minDistance2 = minDistance * minDistance;
	for (size_t i = 0; i < poly.size(); i++) {
		Point curr = poly[i];
		Point next = poly[(i + 1) % poly.size()];
		while (PointUtils::Size2(curr - next) > minDistance2) {
			Micron dist = PointUtils::Size(curr - next);
			Point added = curr + normal(next - curr, dist / 2);
			poly.insert(poly.begin() + i + 1, added);
			next = added;
		}
	}
}

void Polygons::Skew(Polygon& poly, Micron factor, Micron window)
{
	if (factor == 0) return;
	const auto sz = poly.size();
	Polygon ret(sz);

	for (size_t i = 0; i < sz; i++) {
		Point prev = GetPointFrom(poly, -window / 2, i);
		const auto& curr = poly[i];
		Point next = GetPointFrom(poly, window / 2, i);

		auto turnAngle = std::abs(PointUtils::TurnAngle(prev, curr, next));
		Point deltaXY(0, 0);
		if (turnAngle > 0) {
			auto verticalDir = PointUtils::Normal(curr - prev, 1000ll) + PointUtils::Normal(curr - next, 1000ll);
			deltaXY = PointUtils::Normal(verticalDir, std::abs(turnAngle) * factor);
		}
		ret[i] = curr + deltaXY;
	}

	poly = std::move(ret);
}
