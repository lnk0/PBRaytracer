#pragma once

#include "Vec3.h"

class Ray
{
private:
    Vec3 m_origin;
    Vec3 m_direction;

public:
    Ray(const Vec3& origin, const Vec3& direction) : m_origin(origin), m_direction(direction) {}

    inline Vec3 origin() const { return m_origin; }
    inline Vec3 direction() const { return m_direction; }
    inline Vec3 point_at(float t) const { return m_origin + t * m_direction; }
};