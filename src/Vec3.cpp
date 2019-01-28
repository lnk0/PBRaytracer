#include "Vec3.h"

Vec3::Vec3(float v)
{
    m_Elements[0] = v;
    m_Elements[1] = v;
    m_Elements[2] = v;
}

Vec3::Vec3(float v0, float v1, float v2)
{
    m_Elements[0] = v0;
    m_Elements[1] = v1;
    m_Elements[2] = v2;
}

Vec3& Vec3::operator=(const Vec3& v0)
{
    m_Elements[0] = v0.m_Elements[0];
    m_Elements[1] = v0.m_Elements[1];
    m_Elements[2] = v0.m_Elements[2];

    return *this;
}

// Operator overloads

Vec3 operator*(const Vec3& v0, const Vec3& v1)
{
    return Vec3(v0.x() * v1.x(), v0.y() * v1.y(), v0.z() * v1.z());
}

Vec3 operator*(float v0, const Vec3& v1)
{
    return Vec3(v1.x() * v0, v1.y() * v0, v1.z() * v0);
}

Vec3 operator*(const Vec3& v0, float v1)
{
    return Vec3(v0.x() * v1, v0.y() * v1, v0.z() * v1);
}

Vec3 operator/(const Vec3& v0, const Vec3& v1)
{
    return Vec3(v0.x() / v1.x(), v0.y() / v1.y(), v0.z() / v1.z());
}

Vec3 operator/(const Vec3& v0, float v1)
{
    return Vec3(v0.x() / v1, v0.y() / v1, v0.z() / v1);
}

Vec3 operator+(const Vec3& v0, const Vec3& v1)
{
    return Vec3(v0.x() + v1.x(), v0.y() + v1.y(), v0.z() + v1.z());
}

Vec3 operator+(const Vec3& v0, float v1)
{
    return Vec3(v0.x() + v1, v0.y() + v1, v0.z() + v1);
}

Vec3 operator-(const Vec3& v0, const Vec3& v1)
{
    return Vec3(v0.x() - v1.x(), v0.y() - v1.y(), v0.z() - v1.z());
}

Vec3 operator-(const Vec3& v0, float v1)
{
    return Vec3(v0.x() - v1, v0.y() - v1, v0.z() - v1);
}