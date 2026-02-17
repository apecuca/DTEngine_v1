#ifndef INCLUDED_UTILS_H
#define INCLUDED_UTILS_H

namespace DTEngine
{

struct Vector2
{
public:
    ~Vector2() = default;
    Vector2();
    Vector2(const Vector2& _other);
    Vector2(float _x, float _y);

public:
    static float Distance(const Vector2& a, const Vector2& b);

public:
    float x, y;
};

struct Vector3 : public Vector2
{
public:
    ~Vector3() = default;
    Vector3();
    Vector3(const Vector2& _other);
    Vector3(const Vector3& _other);
    Vector3(float _x, float _y, float _z);

public:
    static float Distance(const Vector3& a, const Vector3& b);

public:
    float z;

};

}

#endif