#include <Utils.hpp>

#include <cmath>

using namespace DTEngine;

//
// VECTOR2
//

Vector2::Vector2() :
    x(0.0f), y(0.0f)
{
    //
}

Vector2::Vector2(const Vector2& _other) :
    x(_other.x), y(_other.y)
{
    //
}

Vector2::Vector2(float _x, float _y) :
    x(_x), y(_y)
{
    //
}

float Vector2::Distance(const Vector2& a, const Vector2& b) 
{
    float d = ((b.x - a.x) * (b.x - a.x));
    d += ((b.y - a.y) * (b.y - a.y));
    d = std::sqrt(d);

    return d;
}

void Vector2::Rotate(float degrees)
{
    float radians = degrees * (PI / 180.0f);

    float c = std::cos(radians);
    float s = std::sin(radians);

    float originalX = x;
    x = originalX * c - y * s;
    y = originalX * s + y * c;
}

namespace DTEngine
{

Vector2 operator+ (const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 operator* (const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

} // namespace DTEngine

//
// VECTOR3
//

Vector3::Vector3() :
    Vector2(),
    z(0.0f)
{
    //
}

Vector3::Vector3(const Vector2& _other) :
    Vector2(_other),
    z(0.0f)
{
    //
}

Vector3::Vector3(const Vector3& _other) :
    Vector2(_other),
    z(_other.z)
{
    //
}

Vector3::Vector3(float _x, float _y, float _z) :
    Vector2(_x, _y),
    z(_z)
{
    //
}

float Vector3::Distance(const Vector3& a, const Vector3& b) 
{
    float d = ((b.x - a.x) * (b.x - a.x));
	d += ((b.y - a.y) * (b.y - a.y));
	d += ((b.z - a.z) * (b.z - a.z));
	d = std::sqrt(d);

	return d;
}

//
// VECTOR4
//

Vector4::Vector4() :
    Vector3(),
    w(0.0f)
{
    //
}

Vector4::Vector4(const Vector2& _other) :
    Vector3(_other),
    w(0.0f)
{
    //
}

Vector4::Vector4(const Vector3& _other) :
    Vector3(_other),
    w(0.0f)
{
    //
}

Vector4::Vector4(const Vector4& _other) :
    Vector3(_other.x, _other.y, _other.z),
    w(0.0f)
{
    //
}

Vector4::Vector4(float _x, float _y, float _z, float _w) :
    Vector3(_x, _y, _z),
    w(_w)
{
    //
}