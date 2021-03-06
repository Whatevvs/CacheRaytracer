#pragma once
#include "Primitive.h"

class AABB : public Primitive
{
public:
	AABB(const Vector3& position, const Vector3& size, unsigned int color);

	virtual float HasHit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;

	Vector3 boxMin;
	Vector3 boxMax;
};