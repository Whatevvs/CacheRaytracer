#pragma once

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
    union
    {
        float vec[2];
        struct
        {
            float x;
            float y;
        };
    };

    Vector2 operator+(const Vector2& other) { return {x + other.x, y + other.y}; };
    Vector2 operator-(const Vector2& other) { return {x - other.x, y - other.y}; };
    Vector2 operator*(const Vector2& other) { return {x * other.x, y * other.y}; };
    Vector2 operator/(const Vector2& other) { return {x / other.x, y / other.y}; };
    Vector2& operator+=(const Vector2& rhs){ this->x += rhs.x; this->y += rhs.y; return *this; }
    Vector2& operator-=(const Vector2& rhs){ this->x -= rhs.x; this->y -= rhs.y; return *this; }
    Vector2& operator*=(const Vector2& rhs){ this->x *= rhs.x; this->y *= rhs.y; return *this; }
    Vector2& operator/=(const Vector2& rhs){ this->x /= rhs.x; this->y /= rhs.y; return *this; }

    Vector2 operator*(const float& other) { return {x * other, y * other}; };
    Vector2 operator/(const float& other) { float scalar = 1.0f / other; return {x * scalar, y * scalar}; };
};

struct Vector3
{
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

    Vector3 operator+(const Vector3& other) { return {x + other.x, y + other.y, z + other.z}; };
    Vector3 operator-(const Vector3& other) { return {x - other.x, y - other.y, z - other.z}; };
    Vector3 operator*(const Vector3& other) { return {x * other.x, y * other.y, z * other.z}; };
    Vector3 operator/(const Vector3& other) { return {x / other.x, y / other.y, z / other.z}; };
    Vector3& operator+=(const Vector3& rhs){ this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
    Vector3& operator-=(const Vector3& rhs){ this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
    Vector3& operator*=(const Vector3& rhs){ this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; return *this; }
    Vector3& operator/=(const Vector3& rhs){ this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; return *this; }


    Vector3 operator*(const float& other) { return {x * other, y * other, z * other}; };
    Vector3 operator/(const float& other) { float scalar = 1.0f / other; return {x * scalar, y * scalar, z * scalar}; };
};

struct Vector4
{
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

    Vector4 operator+(const Vector4& other) { return {x + other.x, y + other.y, z + other.z, w + other.w}; };
    Vector4 operator-(const Vector4& other) { return {x - other.x, y - other.y, z - other.z, w - other.w}; };
    Vector4 operator*(const Vector4& other) { return {x * other.x, y * other.y, z * other.z, w * other.w}; };
    Vector4 operator/(const Vector4& other) { return {x / other.x, y / other.y, z / other.z, w / other.w}; };
    Vector4& operator+=(const Vector4& rhs){ this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; this->w += rhs.w; return *this; }
    Vector4& operator-=(const Vector4& rhs){ this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; this->w -= rhs.w; return *this; }
    Vector4& operator*=(const Vector4& rhs){ this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; this->w *= rhs.w; return *this; }
    Vector4& operator/=(const Vector4& rhs){ this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; this->w /= rhs.w; return *this; }

    Vector4 operator*(const float& other) { return {x * other, y * other, z * other, w * other}; };
    Vector4 operator/(const float& other) { float scalar = 1.0f / other; return {x * scalar, y * scalar, z * scalar, w * scalar}; };
};

#endif

static_assert(sizeof(Vector2) ==  8, "Vector2 is wrong size.");
static_assert(sizeof(Vector3) == 16, "Vector3 is wrong size.");
static_assert(sizeof(Vector4) == 16, "Vector4 is wrong size.");