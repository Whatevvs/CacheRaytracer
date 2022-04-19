#include "CacheMath.h"

Vector3 normalize(const Vector3& vec)
{
	float invMag = 1.0f / vec.Length();
	return Vector3(vec.x * invMag, vec.y * invMag, vec.z * invMag);
}

Vector4 normalize(const Vector4& vec)
{
    return Vector4();
}