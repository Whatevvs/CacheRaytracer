#include "Precomp.h"
#include "Sphere.h"

Sphere::Sphere(float radius, const Vector3& position, unsigned int color)
    : m_radius(radius),
    m_position(position),
    m_radiusSquared(radius * radius)
{

    Color = color;
}

float Sphere::HasHit(const Ray& ray, float tMin, float tMax) const
{
    Vector3 oc = ray.origin - m_position;
    auto a = ray.direction.SqrLength();//.length_squared();
    auto half_b = Dot(oc,ray.direction);//dot(oc, r.direction());
    auto c = oc.SqrLength() - m_radiusSquared;//oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < tMin || tMax < root) 
    {
        root = (-half_b + sqrtd) / a;

        if (root < tMin || tMax < root)
            return 0.0f;
    }

    return root;
}