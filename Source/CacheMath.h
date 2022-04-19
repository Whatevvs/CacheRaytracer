#pragma once

#include <cmath>

// #define NON_UNION_VEC

#ifdef NON_UNION_VEC

struct Vector2
{
    float vec[2];
    float &x() { return vec[0]; }
    float &y() { return vec[1]; }
    const float &x() const { return vec[0]; }
    const float &y() const { return vec[1]; }

    Vector2 operator+(const Vector2& other) { return {vec[0] + other.vec[0], vec[1] + other.vec[1]}; };
    Vector2 operator-(const Vector2& other) { return {vec[0] - other.vec[0], vec[1] - other.vec[1]}; };
    Vector2 operator*(const Vector2& other) { return {vec[0] * other.vec[0], vec[1] * other.vec[1]}; };
    Vector2 operator/(const Vector2& other) { return {vec[0] / other.vec[0], vec[1] / other.vec[1]}; };
    Vector2& operator+=(const Vector2& rhs){ this->vec[0] += rhs.vec[0]; this->vec[1] += rhs.vec[1]; return *this; }
    Vector2& operator-=(const Vector2& rhs){ this->vec[0] -= rhs.vec[0]; this->vec[1] -= rhs.vec[1]; return *this; }
    Vector2& operator*=(const Vector2& rhs){ this->vec[0] *= rhs.vec[0]; this->vec[1] *= rhs.vec[1]; return *this; }
    Vector2& operator/=(const Vector2& rhs){ this->vec[0] /= rhs.vec[0]; this->vec[1] /= rhs.vec[1]; return *this; }

    Vector2 operator*(const float& other) { return {vec[0] * other, vec[1] * other}; };
    Vector2 operator/(const float& other) { float scalar = 1.0f / other; return {vec[0] * scalar, vec[1] * scalar}; };
};

struct Vector3
{
    float vec[4];
    float &x() { return vec[0]; }
    float &y() { return vec[1]; }
    float &z() { return vec[2]; }
    float &dummy() { return vec[3]; }
    const float &x() const { return vec[0]; }
    const float &y() const { return vec[1]; }
    const float &z() const { return vec[2]; }
    const float &dummy() const { return vec[3]; }

    Vector3 operator+(const Vector3& other) { return {vec[0] + other.vec[0], vec[1] + other.vec[1], vec[2] + other.vec[2]}; };
    Vector3 operator-(const Vector3& other) { return {vec[0] - other.vec[0], vec[1] - other.vec[1], vec[2] - other.vec[2]}; };
    Vector3 operator*(const Vector3& other) { return {vec[0] * other.vec[0], vec[1] * other.vec[1], vec[2] * other.vec[2]}; };
    Vector3 operator/(const Vector3& other) { return {vec[0] / other.vec[0], vec[1] / other.vec[1], vec[2] / other.vec[2]}; };
    Vector3& operator+=(const Vector3& rhs){ this->vec[0] += rhs.vec[0]; this->vec[1] += rhs.vec[1]; this->vec[2] += rhs.vec[2]; return *this; }
    Vector3& operator-=(const Vector3& rhs){ this->vec[0] -= rhs.vec[0]; this->vec[1] -= rhs.vec[1]; this->vec[2] -= rhs.vec[2]; return *this; }
    Vector3& operator*=(const Vector3& rhs){ this->vec[0] *= rhs.vec[0]; this->vec[1] *= rhs.vec[1]; this->vec[2] *= rhs.vec[2]; return *this; }
    Vector3& operator/=(const Vector3& rhs){ this->vec[0] /= rhs.vec[0]; this->vec[1] /= rhs.vec[1]; this->vec[2] /= rhs.vec[2]; return *this; }


    Vector3 operator*(const float& other) { return {vec[0] * other, vec[1] * other, vec[2] * other}; };
    Vector3 operator/(const float& other) { float scalar = 1.0f / other; return {vec[0] * scalar, vec[1] * scalar, vec[2] * scalar}; };
};

struct Vector4
{
    float vec[4];
    float &x() { return vec[0]; }
    float &y() { return vec[1]; }
    float &z() { return vec[2]; }
    float &w() { return vec[3]; }
    const float &x() const { return vec[0]; }
    const float &y() const { return vec[1]; }
    const float &z() const { return vec[2]; }
    const float &w() const { return vec[3]; }

    Vector4 operator+(const Vector4& other) { return {vec[0] + other.vec[0], vec[1] + other.vec[1], vec[2] + other.vec[2], vec[3] + other.vec[3]}; };
    Vector4 operator-(const Vector4& other) { return {vec[0] - other.vec[0], vec[1] - other.vec[1], vec[2] - other.vec[2], vec[3] - other.vec[3]}; };
    Vector4 operator*(const Vector4& other) { return {vec[0] * other.vec[0], vec[1] * other.vec[1], vec[2] * other.vec[2], vec[3] * other.vec[3]}; };
    Vector4 operator/(const Vector4& other) { return {vec[0] / other.vec[0], vec[1] / other.vec[1], vec[2] / other.vec[2], vec[3] / other.vec[3]}; };
    Vector4& operator+=(const Vector4& rhs){ this->vec[0] += rhs.vec[0]; this->vec[1] += rhs.vec[1]; this->vec[2] += rhs.vec[2]; this->vec[3] += rhs.vec[3]; return *this; }
    Vector4& operator-=(const Vector4& rhs){ this->vec[0] -= rhs.vec[0]; this->vec[1] -= rhs.vec[1]; this->vec[2] -= rhs.vec[2]; this->vec[3] -= rhs.vec[3]; return *this; }
    Vector4& operator*=(const Vector4& rhs){ this->vec[0] *= rhs.vec[0]; this->vec[1] *= rhs.vec[1]; this->vec[2] *= rhs.vec[2]; this->vec[3] *= rhs.vec[3]; return *this; }
    Vector4& operator/=(const Vector4& rhs){ this->vec[0] /= rhs.vec[0]; this->vec[1] /= rhs.vec[1]; this->vec[2] /= rhs.vec[2]; this->vec[3] /= rhs.vec[3]; return *this; }

    Vector4 operator*(const float& other) { return {vec[0] * other, vec[1] * other, vec[2] * other, vec[3] * other}; };
    Vector4 operator/(const float& other) { float scalar = 1.0f / other; return {vec[0] * scalar, vec[1] * scalar, vec[2] * scalar, vec[3] * scalar}; };
};
#else

struct Vector2
{
    Vector2() : x(0.0f), y(0.0f) {};
    Vector2(float v) : x(v) {};
    Vector2(float x, float y) : x(x), y(y) {};

    union
    {
        float vec[2];
        struct
        {
            float x;
            float y;
        };
    };

    Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; };
    Vector2 operator-(const Vector2& other) const { return {x - other.x, y - other.y}; };
    Vector2 operator*(const Vector2& other) const { return {x * other.x, y * other.y}; };
    Vector2 operator/(const Vector2& other) const { return {x / other.x, y / other.y}; };
    Vector2& operator+=(const Vector2& rhs){ this->x += rhs.x; this->y += rhs.y; return *this; }
    Vector2& operator-=(const Vector2& rhs){ this->x -= rhs.x; this->y -= rhs.y; return *this; }
    Vector2& operator*=(const Vector2& rhs){ this->x *= rhs.x; this->y *= rhs.y; return *this; }
    Vector2& operator/=(const Vector2& rhs){ this->x /= rhs.x; this->y /= rhs.y; return *this; }

    Vector2 operator*(const float& other) const { return {x * other, y * other}; };
    Vector2 operator/(const float& other) const { float scalar = 1.0f / other; return {x * scalar, y * scalar}; };

    float SqrtLength() const { return (x * x + y * y); };
    float Length() const { return sqrtf(SqrtLength()); };

    void Normalize()
    {
        float invMag = 1.0f / Length();

        x = x * invMag;
        y = y * invMag;
    }
};

struct Vector3
{
    Vector3() : x(0.0f), y(0.0f), z(0.0f), dummy(0.0f) {};
    Vector3(float v) : x(v), y(v), z(v), dummy(0.0f) {};
    Vector3(float x, float y, float z) : x(x), y(y), z(z), dummy(0.0f) {};

    union
    {
        float vec[4];
        struct
        {
            float x;
            float y;
            float z;
            float dummy;
        };
    };

    Vector3 operator+(const Vector3& other) const { return {x + other.x, y + other.y, z + other.z}; };
    Vector3 operator-(const Vector3& other) const { return {x - other.x, y - other.y, z - other.z}; };
    Vector3 operator*(const Vector3& other) const { return {x * other.x, y * other.y, z * other.z}; };
    Vector3 operator/(const Vector3& other) const { return {x / other.x, y / other.y, z / other.z}; };
    Vector3& operator+=(const Vector3& rhs){ this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
    Vector3& operator-=(const Vector3& rhs){ this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
    Vector3& operator*=(const Vector3& rhs){ this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; return *this; }
    Vector3& operator/=(const Vector3& rhs){ this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; return *this; }

    Vector3 operator*(const float& other) const { return {x * other, y * other, z * other}; };
    Vector3 operator/(const float& other) const { float scalar = 1.0f / other; return {x * scalar, y * scalar, z * scalar}; };

    float SqrtLength() const { return (x * x + y * y + z * z); };
    float Length() const { return sqrtf(SqrtLength()); };

    void Normalize()
    {
        float invMag = 1.0f / Length();

        x = x * invMag;
        y = y * invMag;
        z = z * invMag;
    }
};

struct Vector4
{
    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
    Vector4(float v) : x(v), y(v), z(v), w(v) {};
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

    union
    {
        float vec[4];
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
    };

    Vector4 operator+(const Vector4& other) const { return {x + other.x, y + other.y, z + other.z, w + other.w}; };
    Vector4 operator-(const Vector4& other) const { return {x - other.x, y - other.y, z - other.z, w - other.w}; };
    Vector4 operator*(const Vector4& other) const { return {x * other.x, y * other.y, z * other.z, w * other.w}; };
    Vector4 operator/(const Vector4& other) const { return {x / other.x, y / other.y, z / other.z, w / other.w}; };
    Vector4& operator+=(const Vector4& rhs){ this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; this->w += rhs.w; return *this; }
    Vector4& operator-=(const Vector4& rhs){ this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; this->w -= rhs.w; return *this; }
    Vector4& operator*=(const Vector4& rhs){ this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; this->w *= rhs.w; return *this; }
    Vector4& operator/=(const Vector4& rhs){ this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; this->w /= rhs.w; return *this; }

    Vector4 operator*(const float& other) const { return {x * other, y * other, z * other, w * other}; };
    Vector4 operator/(const float& other) const { float scalar = 1.0f / other; return {x * scalar, y * scalar, z * scalar, w * scalar}; };

    float SqrtLength() const { return (x * x + y * y + z * z + w * w); };
    float Length() const { return sqrtf(SqrtLength()); };

    void Normalize()
    {
        float invMag = 1.0f / Length();

        x = x * invMag;
        y = y * invMag;
        z = z * invMag;
        w = w * invMag;
    }
};

#endif

Vector3 normalize(const Vector3& vec);
Vector4 normalize(const Vector4& vec);

static_assert(sizeof(Vector2) ==  8, "Vector2 is wrong size.");
static_assert(sizeof(Vector3) == 16, "Vector3 is wrong size.");
static_assert(sizeof(Vector4) == 16, "Vector4 is wrong size.");