#pragma once

#include <cmath>

class Vec3
{
private:
    float m_elements[3];

public:
    Vec3(float v);
    Vec3(float v1, float v2, float v3);
    Vec3& operator=(const Vec3& v0);

    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-m_elements[0], -m_elements[1], -m_elements[2]); }
    inline float operator[](int i) const { return m_elements[i]; }

    inline float x() const { return m_elements[0]; }
    inline float y() const { return m_elements[1]; }
    inline float z() const { return m_elements[2]; }

    inline float r() const { return m_elements[0]; }
    inline float g() const { return m_elements[1]; }
    inline float b() const { return m_elements[2]; }

    float lenght() const;
};

    Vec3 operator*(const Vec3& v0, const Vec3& v1);
    Vec3 operator*(float v0, const Vec3& v1);
    Vec3 operator*(const Vec3& v0, float v1);

    Vec3 operator/(const Vec3& v0, const Vec3& v1);
    Vec3 operator/(const Vec3& v1, float v0);

    Vec3 operator+(const Vec3& v0, const Vec3& v1);
    Vec3 operator+(const Vec3& v0, float v1);

    Vec3 operator-(const Vec3& v0, const Vec3& v1);
    Vec3 operator-(const Vec3& v0, float v1);

    Vec3 unit_vector(Vec3 v);