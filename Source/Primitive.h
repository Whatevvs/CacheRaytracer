#pragma once

#include "CacheMath.h"
#include "Ray.h"

class Primitive;

struct HitRecord
{
	Primitive* object;
	Vector3 hitPoint;
	Vector3 normal;
	float t;
	bool frontFace;

	inline void SetFaceNormal(const Ray& ray, const Vector3& outwardNormal)
	{
		frontFace = Dot(ray.direction, outwardNormal) < 0.0f;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

/// <summary>
/// Base class of any primitive that can be intersected by rays
/// </summary>
class Primitive
{
public: 
	virtual float HasHit(const Ray& ray, float tMin, float tMax, HitRecord& record) const = 0;

	Vector3 Color; // temporary for testing
};