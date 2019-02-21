#pragma once

#include "Ray.h"
#include "Vec3.h"

struct HitRecord
{
    float t;
    Vec3 position;
    Vec3 normal;
};

class GeometricObj
{
public:
    virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& hit_record) const = 0;
};