#pragma once

struct Ray;

/// <summary>
/// Base class of any primitive that can be intersected by rays
/// </summary>
class Primitive
{
public: 
	virtual bool HasHit(const Ray& ray, float tMin, float tMax) const = 0;

	unsigned int Color; // temporary for testing
};