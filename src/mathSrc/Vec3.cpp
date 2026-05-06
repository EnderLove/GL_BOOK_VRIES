#include <math.h>
#include <assert.h>
#include "mathHeaders/Vec3.h"

inline Vec3::Vec3() : x(0), y(0), z(0) {}

inline Vec3::Vec3(float value) : x(value), y(value), z(value) {}

inline Vec3::Vec3(const Vec3 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

inline Vec3::Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

inline Vec3::Vec3(const float *xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) {}

inline Vec3 &Vec3::operator = (const Vec3 &rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

inline Vec3 &Vec3::operator = (const float *rhs) {
    x = rhs[0];
    y = rhs[1];
    z = rhs[2];
    return *this;
}

inline bool Vec3::operator == (const Vec3 &rhs) const {
    if (x != rhs.x) return false;
    if (y != rhs.y) return false;
    if (z != rhs.z) return false;
    return true;
}

inline bool Vec3::operator != (const Vec3 &rhs) const {
    if (*this == rhs) return false;
    return true;
}

inline Vec3 Vec3::operator + (const Vec3 &rhs) const {
    Vec3 temp;
    temp.x = x + rhs.x;
    temp.y = y + rhs.y;
    temp.z = z + rhs.z;
    return temp;
}

inline const Vec3 &Vec3::operator += (const Vec3 &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

inline const Vec3 &Vec3::operator -= (const Vec3 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

inline Vec3 Vec3::operator - (const Vec3 &rhs) const {
    Vec3 temp;
    temp.x = x - rhs.x;
    temp.y = y - rhs.y;
    temp.z = z - rhs.z;
    return temp;
}

inline Vec3 Vec3::operator * (const float rhs) const {
    Vec3 temp;
    temp.x = x * rhs;
    temp.y = y * rhs;
    temp.z = z * rhs;
    return temp;
}

inline Vec3 Vec3::operator / (const float rhs) const {
    Vec3 temp;
    temp.x = x / rhs;
    temp.y = y / rhs;
    temp.z = z / rhs;
    return temp;
}

inline const Vec3 &Vec3::operator *= (const float rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

inline const Vec3 &Vec3::operator /= (const float rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

inline float Vec3::operator [] (const int idx) const {
    assert( idx >= 0 && idx < 3 );
    return (&x)[idx];
}

inline float &Vec3::operator [] (const int idx) {
    assert( idx >= 0 && idx < 3 );
    return (&x)[idx];
}

inline Vec3 Vec3::Cross(const Vec3 &rhs) const {
    // this is A and rhs is B (A x B)
    Vec3 temp;
    temp.x = (y * rhs.z) - (rhs.y * z);
    temp.y = (z * rhs.x) - (rhs.z * x);
    temp.z = (x * rhs.y) - (rhs.x * y);
    return temp;
}

inline float Vec3::Dot(const Vec3 &rhs) const {
    float temp = (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
    return temp;
}

inline const Vec3 &Vec3::Normalize() {
    float mag = GetMagnitude();
    float invMag = 1.0f / mag;
    if (0.0f * invMag == 0.0f * invMag){
        x *= invMag;
        y *= invMag;
        z *= invMag;
    }
    return *this;
}

inline float Vec3::GetMagnitude() const {
    float mag;
    mag = x * x + y * y + z * z;
    mag = sqrtf(mag);
    return mag;
}

inline bool Vec3::IsValid() const {
    if (x * 0.0f != x * 0.0f) return false;
    if (y * 0.0f != y * 0.0f) return false;
    if (z * 0.0f != z * 0.0f) return false;
    return true;
}

inline void Vec3::GetOrtho(Vec3 &u, Vec3 &v) const {
    Vec3 n = *this;
    n.Normalize();

    const Vec3 w = (n.z * n.z > 0.9f * 0.9f) ? Vec3(1.0f, 0.0f, 0.0f) : Vec3(0.0f, 0.0f, 1.0f);
    u = w.Cross(n);
    u.Normalize();

    v = n.Cross(u);
    v.Normalize();
    u = v.Cross(n);
    u.Normalize();
}
