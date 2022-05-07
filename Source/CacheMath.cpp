#include "CacheMath.h"

Vector3 Normalize(const Vector3& vec)
{
	// Inverse magnitude
	float invMag = 1.0f / vec.Length();
	return Vector3(vec.x * invMag, vec.y * invMag, vec.z * invMag);
}

Vector4 Normalize(const Vector4& vec)
{
	// Inverse magnitude
	float invMag = 1.0f / vec.Length();
	return Vector4(vec.x * invMag, vec.y * invMag, vec.z * invMag,vec.w * invMag);
}

float Dot(const Vector2& a, const Vector3& b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

float Dot(const Vector3& a, const Vector3& b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

float Dot(const Vector4& a, const Vector4& b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.y * b.z - a.z * b.y, 
		a.z * b.x - a.x * b.z, 
		a.x * b.y - a.y * b.x);
}

float Clamp(float v, float min, float max)
{
	if (v < min) return min;
	if (v > max) return max;
	return v;
}
