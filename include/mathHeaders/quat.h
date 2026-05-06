#ifndef QUAT_H
#define QUAT_H

class Quat{
    public:
        Quat();
        Quat(const Quat &rhs);
        Quat(float x, float y, float z, float w);
        Quat(Vec3 n, const float angleRadians);
};

#endif // QUAT_H!
