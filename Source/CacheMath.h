#pragma once

#include <cmath>

const float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170678214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038194428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141277245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116093305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194919833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405130005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589234201995611212902196086403441815981362977477130996051870721134999999837297804995105973173281609631855024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147305982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989f;

struct Vector2
{
    Vector2() : x(0.0f), y(0.0f) {};
    Vector2(float v) : x(v), y(v) {};
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

    float SqrLength() const { return (x * x + y * y); };
    float Length() const { return sqrtf(SqrLength()); };
    Vector2 Normalized() const 
    { 
        float invMag = 1.0f / Length();
        Vector2 result = {x * invMag, y * invMag};
        return result;
    }


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

    Vector3 operator-() const { return Vector3(-x, -y, -z); }
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

    float SqrLength() const { return (x * x + y * y + z * z); };
    float Length() const { return sqrtf(SqrLength()); };
    Vector3 Normalized() const 
    { 
        float invMag = 1.0f / Length();
        Vector3 result = {x * invMag, y * invMag, z * invMag};
        return result;
    }

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

    float SqrLength() const { return (x * x + y * y + z * z + w * w); };
    float Length() const { return sqrtf(SqrLength()); };
    Vector4 Normalized() const 
    { 
        float invMag = 1.0f / Length();
        Vector4 result = {x * invMag, y * invMag, z * invMag, w * invMag};
        return result;
    }

    void Normalize()
    {
        float invMag = 1.0f / Length();

        x = x * invMag;
        y = y * invMag;
        z = z * invMag;
        w = w * invMag;
    }
};

Vector3 Normalize(const Vector3& vec);
Vector4 Normalize(const Vector4& vec);

float Dot(const Vector2& a, const Vector3& b);
float Dot(const Vector3& a, const Vector3& b);
float Dot(const Vector4& a, const Vector4& b);

Vector3 Cross(const Vector3& a, const Vector3& b);

float Clamp(float v, float min, float max);

static_assert(sizeof(Vector2) ==  8, "Vector2 is wrong size.");
static_assert(sizeof(Vector3) == 16, "Vector3 is wrong size.");
static_assert(sizeof(Vector4) == 16, "Vector4 is wrong size.");

inline float Lerp(float a, float b, float t) {return (a * (1.0f - t) + b * t);}