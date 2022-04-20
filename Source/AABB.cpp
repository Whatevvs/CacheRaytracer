#include "Precomp.h"
#include "AABB.h"

AABB::AABB(const Vector3& position, const Vector3& size, unsigned int color)
{
    boxMin = position - size;
    boxMax = position + size;

    Color = color;
}

float AABB::HasHit(const Ray& ray, float tMin, float tMax) const
{
    for (int a = 0; a < 3; a++)
    {
        float invD = 1.0f / ray.direction.vec[a];
        float t0 = (boxMin.vec[a] - ray.origin.vec[a]) * invD;
        float t1 = (boxMax.vec[a] - ray.origin.vec[a]) * invD;

        if (invD < 0.0f)
        {
            float temp = t1;
            t1 = t0;
            t0 = temp;
        }

        tMin = t0 > tMin ? t0 : tMin;
        tMax = t1 < tMax ? t1 : tMax;

        if (tMax <= tMin)
            return 0.0f;
    }

    return tMin;
}