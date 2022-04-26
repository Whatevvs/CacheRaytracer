#include "Precomp.h"
#include "Sphere.h"

Sphere::Sphere(float radius, const Vector3& position, Vector3 color)
	: m_radius(radius),
	m_position(position),
	m_radiusSquared(radius* radius)
{
	Color = color;
}

float Sphere::HasHit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
{
	Vector3 oc = ray.origin - m_position;
	float a = ray.direction.SqrLength();
	float half_b = Dot(oc, ray.direction);
	float c = oc.SqrLength() - m_radiusSquared;

	float discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	float sqrtd = sqrtf(discriminant);

	// Find the nearest root that lies in the acceptable range.
	float root = (-half_b - sqrtd) / a;
	if (root < tMin || tMax < root)
	{
		root = (-half_b + sqrtd) / a;

		if (root < tMin || tMax < root)
			return 0.0f;
	}

	record.object = (Primitive*)this;
	record.t = root;
	record.hitPoint = ray.At(root);
	record.SetFaceNormal(ray, record.hitPoint - m_position);

	return root;
}