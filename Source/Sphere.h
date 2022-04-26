#pragma once
#include "Primitive.h"

class Sphere : public Primitive
{
public:
	Sphere(float radius, const Vector3& position, Vector3 color);

	virtual float HasHit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;

	float m_radius;
	Vector3 m_position;
private:
	float m_radiusSquared;
};