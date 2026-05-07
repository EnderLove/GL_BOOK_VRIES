#ifndef VEC_4_H
#define VEC_4_H

class Vec4{
    public:
        float x;
        float y;
        float z;
        float w;

    public:
        Vec4();
        Vec4(const float value);
        Vec4(const Vec4 &rhs);
        Vec4(float X, float Y, float Z, float W);
        Vec4(const float *rhs);
        Vec4 &operator = (const Vec4 &rhs);

        bool        operator == (const Vec4 &rhs) const;
        bool        operator != (const Vec4 &rhs) const;
        Vec4        operator +  (const Vec4 &rhs) const;
        const Vec4 &operator += (const Vec4 &rhs);
        const Vec4 &operator -= (const Vec4 &rhs);
        const Vec4 &operator *= (const Vec4 &rhs);
        const Vec4 &operator /= (const Vec4 &rhs);
        Vec4        operator -  (const Vec4 &rhs) const;
        Vec4        operator *  (const float rhs) const;
        float       operator [] (const int idx) const;
        float      &operator [] (const int idx);

        float Dot(const Vec4 &rhs) const;
        const Vec4 &Normalize();
        float GetMagnitude() const;
        bool IsValid() const;
        void Zero() { x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f; }

        const float *ToPtr() const { return &x; }
        float *ToPtr() { return &x; }
};

#endif // VEC_4_H!
