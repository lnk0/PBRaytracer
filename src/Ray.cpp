#include "Ray.h"

Ray::Ray(const Vec3& origin, const Vec3& direction) : m_origin(origin), m_direction(direction)
{
}

Vec3 Ray::origin() const
{
    return m_origin;
}

Vec3 Ray::direction() const
{
    return m_direction;
}

Vec3 Ray::point_at(float t) const
{
    return m_origin + t * m_direction;
}