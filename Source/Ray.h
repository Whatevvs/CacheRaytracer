#pragma once

struct Ray
{
	Ray() {};
	Ray(const Vector3& start, const Vector3& dir) : origin(start), direction(dir) {}

	Vector3 At(float t) const
	{
		return origin + direction * t;
	}

	Vector3 origin;
	Vector3 direction;
};