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

Vector2::Vector2(float _x, float _y) :
    x(_x), y(_y)
{
    //
}

Vector2 Vector2::operator- () const
{
    return Vector2(-x, -y);
}

Vector2& Vector2::operator+= (const Vector2& rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

Vector2& Vector2::operator-= (const Vector2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

Vector2& Vector2::operator*= (const Vector2& rhs)
{
    x *= rhs.x;
    y *= rhs.y;

    return *this;
}

Vector2& Vector2::operator/= (const Vector2& rhs)
{
    x /= rhs.x;
    y /= rhs.y;

    return *this;
}

Vector2& Vector2::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

Vector2& Vector2::operator/= (float scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}

float Vector2::Length() const
{
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::Normalized() const
{
    float length = Length();

    return Vector2(x / length, y / length);
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

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
    return a.x * b.x + a.y * b.y;
}

float Vector2::Distance(const Vector2& a, const Vector2& b)
{
    float d = ((b.x - a.x) * (b.x - a.x));
    d += ((b.y - a.y) * (b.y - a.y));
    d = std::sqrt(d);

    return d;
}

namespace DTEngine
{

Vector2 operator+ (const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 operator- (const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2 operator* (const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

Vector2 operator/ (const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
}

Vector2 operator* (const Vector2& lhs, float scalar)
{
    return Vector2(lhs.x * scalar, lhs.y * scalar);
}

Vector2 operator* (float scalar, const Vector2& rhs)
{
    return Vector2(scalar * rhs.x, scalar * rhs.y);
}

Vector2 operator/ (const Vector2& lhs, float scalar)
{
    return Vector2(lhs.x / scalar, lhs.y / scalar);
}

bool operator== (const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!= (const Vector2& lhs, const Vector2& rhs)
{
    return !(lhs == rhs);
}

} // namespace DTEngine

//
// VECTOR3
//

Vector3::Vector3() :
    x(0.0f), y(0.0f), z(0.0f)
{
    //
}

Vector3::Vector3(float _x, float _y, float _z) :
    x(_x), y(_y), z(_z)
{
    //
}

Vector3::Vector3(const Vector2& _xy, float _z) :
    x(_xy.x), y(_xy.y), z(_z)
{
    //
}

Vector3 Vector3::operator- () const
{
    return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+= (const Vector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
}

Vector3& Vector3::operator-= (const Vector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
}

Vector3& Vector3::operator*= (const Vector3& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;

    return *this;
}

Vector3& Vector3::operator/= (const Vector3& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;

    return *this;
}

Vector3& Vector3::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

Vector3& Vector3::operator/= (float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
}

float Vector3::Length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::Normalized() const
{
    float length = Length();

    return Vector3(x / length, y / length, z / length);
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vector3::Distance(const Vector3& a, const Vector3& b)
{
    float d = ((b.x - a.x) * (b.x - a.x));
    d += ((b.y - a.y) * (b.y - a.y));
    d += ((b.z - a.z) * (b.z - a.z));
    d = std::sqrt(d);

    return d;
}

namespace DTEngine
{

Vector3 operator+ (const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3 operator- (const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector3 operator* (const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

Vector3 operator/ (const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

Vector3 operator* (const Vector3& lhs, float scalar)
{
    return Vector3(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar);
}

Vector3 operator* (float scalar, const Vector3& rhs)
{
    return Vector3(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z);
}

Vector3 operator/ (const Vector3& lhs, float scalar)
{
    return Vector3(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar);
}

bool operator== (const Vector3& lhs, const Vector3& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!= (const Vector3& lhs, const Vector3& rhs)
{
    return !(lhs == rhs);
}

} // namespace DTEngine

//
// VECTOR4
//

Vector4::Vector4() :
    x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
    //
}

Vector4::Vector4(float _x, float _y, float _z, float _w) :
    x(_x), y(_y), z(_z), w(_w)
{
    //
}

Vector4::Vector4(const Vector3& _xyz, float _w) :
    x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w)
{
    //
}

Vector4 Vector4::operator- () const
{
    return Vector4(-x, -y, -z, -w);
}

Vector4& Vector4::operator+= (const Vector4& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

Vector4& Vector4::operator-= (const Vector4& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

Vector4& Vector4::operator*= (const Vector4& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;

    return *this;
}

Vector4& Vector4::operator/= (const Vector4& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;

    return *this;
}

Vector4& Vector4::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

Vector4& Vector4::operator/= (float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;
}

float Vector4::Length() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::Normalized() const
{
    float length = Length();

    return Vector4(x / length, y / length, z / length, w / length);
}

float Vector4::Dot(const Vector4& a, const Vector4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

namespace DTEngine
{

Vector4 operator+ (const Vector4& lhs, const Vector4& rhs)
{
    return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Vector4 operator- (const Vector4& lhs, const Vector4& rhs)
{
    return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

Vector4 operator* (const Vector4& lhs, const Vector4& rhs)
{
    return Vector4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
}

Vector4 operator/ (const Vector4& lhs, const Vector4& rhs)
{
    return Vector4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
}

Vector4 operator* (const Vector4& lhs, float scalar)
{
    return Vector4(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar, lhs.w * scalar);
}

Vector4 operator* (float scalar, const Vector4& rhs)
{
    return Vector4(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z, scalar * rhs.w);
}

Vector4 operator/ (const Vector4& lhs, float scalar)
{
    return Vector4(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar, lhs.w / scalar);
}

bool operator== (const Vector4& lhs, const Vector4& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

bool operator!= (const Vector4& lhs, const Vector4& rhs)
{
    return !(lhs == rhs);
}

} // namespace DTEngine

//
// MATRIX3
//

Matrix3::Matrix3() :
    Matrix3(1.0f)
{
    //
}

Matrix3::Matrix3(const Matrix3& _other)
{
    for (int col = 0; col < 3; col++)
        for (int row = 0; row < 3; row++)
            m[col][row] = _other.m[col][row];
}

Matrix3::Matrix3(float _diagonal)
{
    for (int col = 0; col < 3; col++)
        for (int row = 0; row < 3; row++)
            m[col][row] = col == row ? _diagonal : 0.0f;
}

Matrix3::Matrix3(const Matrix4& _other)
{
    for (int col = 0; col < 3; col++)
        for (int row = 0; row < 3; row++)
            m[col][row] = _other[col][row];
}

Matrix3::Matrix3(const Vector3& _c0, const Vector3& _c1, const Vector3& _c2)
{
    m[0][0] = _c0.x; m[0][1] = _c0.y; m[0][2] = _c0.z;
    m[1][0] = _c1.x; m[1][1] = _c1.y; m[1][2] = _c1.z;
    m[2][0] = _c2.x; m[2][1] = _c2.y; m[2][2] = _c2.z;
}

Matrix3::Matrix3(float _x0, float _y0, float _z0,
                 float _x1, float _y1, float _z1,
                 float _x2, float _y2, float _z2)
{
    m[0][0] = _x0; m[0][1] = _y0; m[0][2] = _z0;
    m[1][0] = _x1; m[1][1] = _y1; m[1][2] = _z1;
    m[2][0] = _x2; m[2][1] = _y2; m[2][2] = _z2;
}

Matrix3 Matrix3::operator* (float scalar) const
{
    Matrix3 result(*this);
    result *= scalar;

    return result;
}

Matrix3& Matrix3::operator*= (const Matrix3& rhs)
{
    *this = *this * rhs;

    return *this;
}

Matrix3& Matrix3::operator*= (float scalar)
{
    for (int col = 0; col < 3; col++)
        for (int row = 0; row < 3; row++)
            m[col][row] *= scalar;

    return *this;
}

Matrix3 Matrix3::Inverse() const
{
    float det = + m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
                - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
                + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);

    float invDet = 1.0f / det;

    Matrix3 result(0.0f);

    // Adjugate over the determinant
    result.m[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invDet;
    result.m[1][0] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]) * invDet;
    result.m[2][0] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invDet;
    result.m[0][1] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]) * invDet;
    result.m[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invDet;
    result.m[2][1] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]) * invDet;
    result.m[0][2] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * invDet;
    result.m[1][2] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]) * invDet;
    result.m[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invDet;

    return result;
}

Matrix3 Matrix3::Translate(const Matrix3& mat, const Vector2& translation)
{
    Matrix3 result(mat);

    for (int row = 0; row < 3; row++)
    {
        result.m[2][row] =
            mat.m[0][row] * translation.x +
            mat.m[1][row] * translation.y +
            mat.m[2][row];
    }

    return result;
}

Matrix3 Matrix3::Rotate(const Matrix3& mat, float angleRadians)
{
    float c = std::cos(angleRadians);
    float s = std::sin(angleRadians);

    Matrix3 result(mat);

    for (int row = 0; row < 3; row++)
    {
        result.m[0][row] = mat.m[0][row] * c + mat.m[1][row] * s;
        result.m[1][row] = mat.m[0][row] * -s + mat.m[1][row] * c;
    }

    return result;
}

Matrix3 Matrix3::Scale(const Matrix3& mat, const Vector2& scale)
{
    Matrix3 result(mat);

    for (int row = 0; row < 3; row++)
    {
        result.m[0][row] = mat.m[0][row] * scale.x;
        result.m[1][row] = mat.m[1][row] * scale.y;
    }

    return result;
}

Matrix3 Matrix3::Ortho(float left, float right, float bottom, float top)
{
    Matrix3 result(1.0f);

    result.m[0][0] = 2.0f / (right - left);
    result.m[1][1] = 2.0f / (top - bottom);
    result.m[2][0] = -(right + left) / (right - left);
    result.m[2][1] = -(top + bottom) / (top - bottom);

    return result;
}

namespace DTEngine
{

Matrix3 operator* (const Matrix3& lhs, const Matrix3& rhs)
{
    Matrix3 result(0.0f);

    for (int col = 0; col < 3; col++)
        for (int row = 0; row < 3; row++)
            for (int k = 0; k < 3; k++)
                result.m[col][row] += lhs.m[k][row] * rhs.m[col][k];

    return result;
}

Vector3 operator* (const Matrix3& lhs, const Vector3& rhs)
{
    return Vector3(
        lhs.m[0][0] * rhs.x + lhs.m[1][0] * rhs.y + lhs.m[2][0] * rhs.z,
        lhs.m[0][1] * rhs.x + lhs.m[1][1] * rhs.y + lhs.m[2][1] * rhs.z,
        lhs.m[0][2] * rhs.x + lhs.m[1][2] * rhs.y + lhs.m[2][2] * rhs.z);
}

bool operator== (const Matrix3& lhs, const Matrix3& rhs)
{
    for (int col = 0; col < 3; col++)
        for (int row = 0; row < 3; row++)
            if (lhs.m[col][row] != rhs.m[col][row])
                return false;

    return true;
}

bool operator!= (const Matrix3& lhs, const Matrix3& rhs)
{
    return !(lhs == rhs);
}

} // namespace DTEngine

//
// MATRIX4
//

Matrix4::Matrix4() :
    Matrix4(1.0f)
{
    //
}

Matrix4::Matrix4(const Matrix4& _other)
{
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            m[col][row] = _other.m[col][row];
}

Matrix4::Matrix4(float _diagonal)
{
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            m[col][row] = col == row ? _diagonal : 0.0f;
}

Matrix4::Matrix4(const Vector4& _c0, const Vector4& _c1, const Vector4& _c2, const Vector4& _c3)
{
    m[0][0] = _c0.x; m[0][1] = _c0.y; m[0][2] = _c0.z; m[0][3] = _c0.w;
    m[1][0] = _c1.x; m[1][1] = _c1.y; m[1][2] = _c1.z; m[1][3] = _c1.w;
    m[2][0] = _c2.x; m[2][1] = _c2.y; m[2][2] = _c2.z; m[2][3] = _c2.w;
    m[3][0] = _c3.x; m[3][1] = _c3.y; m[3][2] = _c3.z; m[3][3] = _c3.w;
}

Matrix4::Matrix4(float _x0, float _y0, float _z0, float _w0,
                 float _x1, float _y1, float _z1, float _w1,
                 float _x2, float _y2, float _z2, float _w2,
                 float _x3, float _y3, float _z3, float _w3)
{
    m[0][0] = _x0; m[0][1] = _y0; m[0][2] = _z0; m[0][3] = _w0;
    m[1][0] = _x1; m[1][1] = _y1; m[1][2] = _z1; m[1][3] = _w1;
    m[2][0] = _x2; m[2][1] = _y2; m[2][2] = _z2; m[2][3] = _w2;
    m[3][0] = _x3; m[3][1] = _y3; m[3][2] = _z3; m[3][3] = _w3;
}

Matrix4 Matrix4::operator* (float scalar) const
{
    Matrix4 result(*this);
    result *= scalar;

    return result;
}

Matrix4& Matrix4::operator*= (const Matrix4& rhs)
{
    *this = *this * rhs;

    return *this;
}

Matrix4& Matrix4::operator*= (float scalar)
{
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            m[col][row] *= scalar;

    return *this;
}

Matrix4 Matrix4::Translate(const Matrix4& mat, const Vector3& translation)
{
    Matrix4 result(mat);

    for (int row = 0; row < 4; row++)
    {
        result.m[3][row] =
            mat.m[0][row] * translation.x +
            mat.m[1][row] * translation.y +
            mat.m[2][row] * translation.z +
            mat.m[3][row];
    }

    return result;
}

Matrix4 Matrix4::Rotate(const Matrix4& mat, float angleRadians, const Vector3& axis)
{
    float c = std::cos(angleRadians);
    float s = std::sin(angleRadians);

    Vector3 a = axis.Normalized();
    Vector3 t(a.x * (1.0f - c), a.y * (1.0f - c), a.z * (1.0f - c));

    // Rodrigues rotation matrix (column-major), as in glm::rotate
    float r[3][3];
    r[0][0] = c + t.x * a.x;
    r[0][1] = t.x * a.y + s * a.z;
    r[0][2] = t.x * a.z - s * a.y;

    r[1][0] = t.y * a.x - s * a.z;
    r[1][1] = c + t.y * a.y;
    r[1][2] = t.y * a.z + s * a.x;

    r[2][0] = t.z * a.x + s * a.y;
    r[2][1] = t.z * a.y - s * a.x;
    r[2][2] = c + t.z * a.z;

    Matrix4 result(mat);

    for (int col = 0; col < 3; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            result.m[col][row] =
                mat.m[0][row] * r[col][0] +
                mat.m[1][row] * r[col][1] +
                mat.m[2][row] * r[col][2];
        }
    }

    return result;
}

Matrix4 Matrix4::Scale(const Matrix4& mat, const Vector3& scale)
{
    Matrix4 result(mat);

    for (int row = 0; row < 4; row++)
    {
        result.m[0][row] = mat.m[0][row] * scale.x;
        result.m[1][row] = mat.m[1][row] * scale.y;
        result.m[2][row] = mat.m[2][row] * scale.z;
    }

    return result;
}

// Right-handed, NDC depth -1..1, as in glm::ortho
Matrix4 Matrix4::Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
    Matrix4 result(1.0f);

    result.m[0][0] = 2.0f / (right - left);
    result.m[1][1] = 2.0f / (top - bottom);
    result.m[2][2] = -2.0f / (zFar - zNear);
    result.m[3][0] = -(right + left) / (right - left);
    result.m[3][1] = -(top + bottom) / (top - bottom);
    result.m[3][2] = -(zFar + zNear) / (zFar - zNear);

    return result;
}

namespace DTEngine
{

Matrix4 operator* (const Matrix4& lhs, const Matrix4& rhs)
{
    Matrix4 result(0.0f);

    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            for (int k = 0; k < 4; k++)
                result.m[col][row] += lhs.m[k][row] * rhs.m[col][k];

    return result;
}

Vector4 operator* (const Matrix4& lhs, const Vector4& rhs)
{
    return Vector4(
        lhs.m[0][0] * rhs.x + lhs.m[1][0] * rhs.y + lhs.m[2][0] * rhs.z + lhs.m[3][0] * rhs.w,
        lhs.m[0][1] * rhs.x + lhs.m[1][1] * rhs.y + lhs.m[2][1] * rhs.z + lhs.m[3][1] * rhs.w,
        lhs.m[0][2] * rhs.x + lhs.m[1][2] * rhs.y + lhs.m[2][2] * rhs.z + lhs.m[3][2] * rhs.w,
        lhs.m[0][3] * rhs.x + lhs.m[1][3] * rhs.y + lhs.m[2][3] * rhs.z + lhs.m[3][3] * rhs.w);
}

bool operator== (const Matrix4& lhs, const Matrix4& rhs)
{
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            if (lhs.m[col][row] != rhs.m[col][row])
                return false;

    return true;
}

bool operator!= (const Matrix4& lhs, const Matrix4& rhs)
{
    return !(lhs == rhs);
}

} // namespace DTEngine