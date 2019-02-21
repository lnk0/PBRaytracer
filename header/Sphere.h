#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "GeometricObj.h"

class Sphere : public GeometricObj
{
private:
    Vec3 m_center;
    float m_radius;

public:
    Sphere(Vec3 center, float radius);
    virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& hit_record) const;
    
};