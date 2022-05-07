#pragma once

#include "Primitive.h"

class Triangle : public Primitive
{
public:
	Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 color);
	virtual float HasHit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;

private:
	Vector3 vertex0;
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 edge1;
	Vector3 edge2;
	Vector3 normal;
};