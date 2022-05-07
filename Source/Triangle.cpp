#include "Triangle.h"

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 color) : vertex0(v0), vertex1(v1), vertex2(v2)
{
	Color = color;
	edge1 = vertex1 - vertex0;
	edge2 = vertex2 - vertex0;
	normal = Cross(edge1, edge2);
	normal.Normalize();
}

float Triangle::HasHit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
{
	// Möller-Trumbore intersection
	// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
	const float epsilon = 0.0000001f;

	Vector3 h = Cross(ray.direction, edge2);
	float a = Dot(edge1, h);
	if (a > -epsilon && a < epsilon) return false;

	float f = 1.0f / a;
	Vector3 s = ray.origin - vertex0;
	float u = f * Dot(s, h);
	if (u < 0.0f || u > 1.0f) return false;

	Vector3 q = Cross(s, edge1);
	float v = f * Dot(ray.direction, q);

	if (v < 0.0 || u + v > 1.0) return false;

	float t = f * Dot(edge2, q);
	
	if (t > epsilon)
	{
		record.object = (Primitive*)this;
		record.t = t;
		record.hitPoint = ray.At(t);
		record.SetFaceNormal(ray, normal);
		return true;
	}
	else
	{
		return false;
	}
}
