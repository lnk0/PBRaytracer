#include "Sphere.h"

Sphere::Sphere(Vec3 center, float radius) : m_center(center), m_radius(radius)
{
}

bool Sphere::hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record) const
{
    Vec3 oc = ray.origin() - m_center;
    float a = dot(ray.direction(), ray.direction());
    float b = dot(oc, ray.direction());
    float c = dot(oc, oc) - m_radius * m_radius;
    float disc = b * b - a * c;
    if (disc > 0)
    {
        float tmp = (-b -sqrt(b * b - a * c)) / a;
        if (tmp < t_max && tmp > t_min)
        {
            hit_record.t = tmp;
            hit_record.position = ray.point_at(hit_record.t);
            hit_record.normal = (hit_record.position - m_center) / m_radius;
            return true;
        }

        tmp = (-b + sqrt(b * b - a * c)) / a;
        if (tmp < t_max && tmp > t_min)
        {
            hit_record.t = tmp;
            hit_record.position = ray.point_at(hit_record.t);
            hit_record.normal = (hit_record.position - m_center) / m_radius;
            return true;
        }        
    }

    return false;
}