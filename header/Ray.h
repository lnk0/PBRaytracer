#pragma once

#include "Vec3.h"

class Ray
{
private:
    Vec3 m_origin;
    Vec3 m_direction;

public:
    Ray(const Vec3& origin, const Vec3& direction);

    Vec3 origin() const;
    Vec3 direction() const;
    Vec3 point_at(float t) const;
};