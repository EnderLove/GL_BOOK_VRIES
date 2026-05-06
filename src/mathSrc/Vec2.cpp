#include <assert.h>
#include <math.h>
#include "mathHeaders/Vec2.h"

inline Vec2::Vec2() : x(0), y(0) {}

inline Vec2::Vec2(const float value) : x(value), y(value) {}

inline Vec2::Vec2(const Vec2 &rhs) : x(rhs.x), y(rhs.y) {}

inline Vec2::Vec2(float X, float Y) : x(X), y(Y) {}

inline Vec2::Vec2(const float *xy) : x(xy[0]), y(xy[1]) {}

inline Vec2 &Vec2::operator = (const Vec2 &rhs){
    x = rhs.x;
    y = rhs.y;
    return *this;
}

inline bool Vec2::operator == (const Vec2 & rhs) const {
    if (x != rhs.x) return false;
    if (y != rhs.y) return false;
    return true;
}

inline bool Vec2::operator != (const Vec2 &rhs) const {
    if (*this == rhs) return false;
    return true;
}

inline Vec2 Vec2::operator + (const Vec2 &rhs) const {
    Vec2 temp;
    temp.x = x + rhs.x;
    temp.y = y + rhs.y;
    return temp;
}

inline const Vec2 &Vec2::operator += (const Vec2 &rhs){
    x += rhs.x;
    y += rhs.y;
    return *this;
}

inline const Vec2 &Vec2::operator -= (const Vec2 &rhs){
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

inline Vec2 Vec2::operator - (const Vec2 &rhs) const {
    Vec2 temp;
    temp.x = x - rhs.x;
    temp.y = y - rhs.y;
    return temp;
}

inline Vec2 Vec2::operator * (const float rhs) const {
    Vec2 temp;
    temp.x = x * rhs;
    temp.y = y * rhs;
    return temp;
}

inline const Vec2 &Vec2::operator *= (const float rhs){
    x *= rhs;
    y *= rhs;
    return *this;
}

inline const Vec2 &Vec2::operator /= (const float rhs){
    x /= rhs;
    y /= rhs;
    return *this;
}

inline float Vec2::operator [] (const int idx) const {
    assert( idx >= 0 && idx < 2 );
    return (&x)[idx];
}

inline float &Vec2::operator [] (const int idx){
    assert( idx >= 0 && idx < 2 );
    return (&x)[idx];
}

inline const Vec2 &Vec2::Normalize(){
    float mag = GetMagnitude();
    float invMag = 1.0f / mag;
    if (0.0f * invMag == 0.0f * invMag){
        x = x * invMag;
        y = y * invMag;
    }
    return *this;
}

inline float Vec2::GetMagnitude() const {
    float mag;

    mag = x * x + y * y;
    mag = sqrtf(mag);

    return mag;
}

inline bool Vec2::IsValid() const {
    if (x * 0.0f != x * 0.0f) return false;
    if (y * 0.0f != y * 0.0f) return false;
    return true;
}


