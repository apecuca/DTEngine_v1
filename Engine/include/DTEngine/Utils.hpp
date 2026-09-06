#ifndef DTENGINE_UTILS_H
#define DTENGINE_UTILS_H

#include <cstdint>

// Mouse Input
#define DTK_MOUSEL      0x00
#define DTK_MOUSER      0x01
#define DTK_MOUSEM      0x02

// Keyboard Input
#define DTK_A           0x41
#define DTK_B           0x42
#define DTK_C           0x43
#define DTK_D           0x44
#define DTK_E           0x45
#define DTK_F           0x46
#define DTK_G           0x47
#define DTK_H           0x48
#define DTK_I           0x49
#define DTK_J           0x4A
#define DTK_K           0x4B
#define DTK_L           0x4C
#define DTK_M           0x4D
#define DTK_N           0x4E
#define DTK_O           0x4F
#define DTK_P           0x50
#define DTK_Q           0x51
#define DTK_R           0x52
#define DTK_S           0x53
#define DTK_T           0x54
#define DTK_U           0x55
#define DTK_V           0x56
#define DTK_W           0x57
#define DTK_X           0x58
#define DTK_Y           0x59
#define DTK_Z           0x5A

#define DTK_ESCAPE      0x1B
#define DTK_BACKSPACE   0x08
#define DTK_CAPSLK      0x14
#define DTK_TAB         0x09
#define DTK_SPACE       0x20
#define DTK_LWIN        0x5B
#define DTK_RWIN        0x5C
#define DTK_LSHIFT      0xA0
#define DTK_RSHIFT      0xA1
#define DTK_LCTRL       0xA2
#define DTK_RCTRL       0xA3
#define DTK_LALT        0xA4
#define DTK_RALT        0xA5
#define DTK_COLON       0xBA
#define DTK_SEMICOLON   0xBA
#define DTK_PLUS        0xBB
#define DTK_EQUAL       0xBB
#define DTK_COMMA       0xBC
#define DTK_LESSTHAN    0xBC
#define DTK_MINUS       0xBD
#define DTK_UNDERSCORE  0xBD
#define DTK_PERIOD      0xBE
#define DTK_GREATERTHAN 0xBE
#define DTK_FSLASH      0xBF
#define DTK_QUESTION    0xBF
#define DTK_GRAVE       0xC0
#define DTK_TILDE       0xC0
#define DTK_LBRACE      0xDB
#define DTK_RBRACE      0xDD
#define DTK_BACKSLASH   0xDC
#define DTK_PIPE        0xDC
#define DTK_APOSTROPHE  0xDE
#define DTK_DQUOTATION  0xDE

#define DTK_ALPHA0      0x30
#define DTK_ALPHA1      0x31
#define DTK_ALPHA2      0x32
#define DTK_ALPHA3      0x33
#define DTK_ALPHA4      0x34
#define DTK_ALPHA5      0x35
#define DTK_ALPHA6      0x36
#define DTK_ALPHA7      0x37
#define DTK_ALPHA8      0x38
#define DTK_ALPHA9      0x39

#define DTK_F1          0x70
#define DTK_F2          0x71
#define DTK_F3          0x72
#define DTK_F4          0x73
#define DTK_F5          0x74
#define DTK_F6          0x75
#define DTK_F7          0x76
#define DTK_F8          0x77
#define DTK_F9          0x78
#define DTK_F10         0x79
#define DTK_F11         0x7A
#define DTK_F12         0x7B
#define DTK_F13         0x7C
#define DTK_F14         0x7D
#define DTK_F15         0x7E
#define DTK_F16         0x7F
#define DTK_F17         0x80
#define DTK_F18         0x81
#define DTK_F19         0x82
#define DTK_F20         0x83
#define DTK_F21         0x84
#define DTK_F22         0x85
#define DTK_F23         0x86
#define DTK_F24         0x87

#define DTK_NUMPAD0     0x60
#define DTK_NUMPAD1     0x61
#define DTK_NUMPAD2     0x62
#define DTK_NUMPAD3     0x63
#define DTK_NUMPAD4     0x64
#define DTK_NUMPAD5     0x65
#define DTK_NUMPAD6     0x66
#define DTK_NUMPAD7     0x67
#define DTK_NUMPAD8     0x68
#define DTK_NUMPAD9     0x69
#define DTK_MULTIPLY    0x6A
#define DTK_ADD         0x6B
#define DTK_SEPARATOR   0x6C
#define DTK_SUBTRACT    0x6D
#define DTK_DECIMAL     0x6E
#define DTK_DIVIDE      0x6F

#define DTK_PAGEUP      0x21
#define DTK_PAGEDOWN    0x22
#define DTK_END         0x23
#define DTK_HOME        0x24
#define DTK_LEFT        0x25
#define DTK_UP          0x26
#define DTK_RIGHT       0x27
#define DTK_DOWN        0x28
#define DTK_SELECT      0x29
#define DTK_EXECUTE     0x2B
#define DTK_INSERT      0x2D
#define DTK_DELETE      0x2E
#define DTK_PRINTSCR    0x2C
#define DTK_SCROLL      0x91
#define DTK_PAUSE       0x13
#define DTK_PRINT       0x2A
#define DTK_HELP        0x2F

#define DTK_APPS        0x5D
#define DTK_SHIFT       0x10
#define DTK_CTRL        0x11
#define DTK_ALT         0x12
#define DTK_SLEEP       0x5F

float constexpr PI = 3.14159265358979f;

namespace DTEngine
{

///
/// FORWARD DECLARATIONS
///

struct Vector2;

///
/// MISC
/// 

typedef uint32_t LayerMask;

// Mask matching every layer
constexpr LayerMask LAYER_MASK_ALL = ~0u;

///
/// MATH
///

namespace DTMath 
{

    // Converts degrees to radians
    constexpr float Radians(float degrees) { return degrees * (PI / 180.0f); }

    float Lerp(float a, float b, float t);
    Vector2 Lerp(Vector2 a, Vector2 b, float t);
}

///
/// VECTORS
/// 

struct Vector2
{
public:
    Vector2();
    Vector2(float _x, float _y);

    Vector2 operator- () const;

    Vector2& operator+= (const Vector2& rhs);
    Vector2& operator-= (const Vector2& rhs);
    Vector2& operator*= (const Vector2& rhs);
    Vector2& operator/= (const Vector2& rhs);
    Vector2& operator*= (float scalar);
    Vector2& operator/= (float scalar);

public:
    // Returns the magnitude of the vector
    float Length() const;
    // Returns this vector with magnitude 1 (undefined for zero-length vectors)
    Vector2 Normalized() const;
    // Rotates the vector counter-clockwise around the origin
    void Rotate(float degrees);

public:
    static float Dot(const Vector2& a, const Vector2& b);
    // Calculates the distance between two vectors
    static float Distance(const Vector2& a, const Vector2& b);

    inline static Vector2 zero() { return Vector2(0.0f, 0.0f); }
    inline static Vector2 one() { return Vector2(1.0f, 1.0f); }
    inline static Vector2 right() { return Vector2(1.0f, 0.0f); }
    inline static Vector2 up() { return Vector2(0.0f, 1.0f); }

public:
    float x, y;
};

// Componentwise arithmetic
Vector2 operator+ (const Vector2& lhs, const Vector2& rhs);
Vector2 operator- (const Vector2& lhs, const Vector2& rhs);
Vector2 operator* (const Vector2& lhs, const Vector2& rhs);
Vector2 operator/ (const Vector2& lhs, const Vector2& rhs);
// Scalar arithmetic
Vector2 operator* (const Vector2& lhs, float scalar);
Vector2 operator* (float scalar, const Vector2& rhs);
Vector2 operator/ (const Vector2& lhs, float scalar);
// Exact float comparison
bool operator== (const Vector2& lhs, const Vector2& rhs);
bool operator!= (const Vector2& lhs, const Vector2& rhs);

struct Vector3
{
public:
    Vector3();
    Vector3(float _x, float _y, float _z);
    Vector3(const Vector2& _xy, float _z);

    Vector3 operator- () const;

    Vector3& operator+= (const Vector3& rhs);
    Vector3& operator-= (const Vector3& rhs);
    Vector3& operator*= (const Vector3& rhs);
    Vector3& operator/= (const Vector3& rhs);
    Vector3& operator*= (float scalar);
    Vector3& operator/= (float scalar);

public:
    // Returns the magnitude of the vector
    float Length() const;
    // Returns this vector with magnitude 1 (undefined for zero-length vectors)
    Vector3 Normalized() const;

public:
    static float Dot(const Vector3& a, const Vector3& b);
    // Calculates the distance between two vectors
    static float Distance(const Vector3& a, const Vector3& b);

    inline static Vector3 zero() { return Vector3(0.0f, 0.0f, 0.0f); }
    inline static Vector3 one() { return Vector3(1.0f, 1.0f, 1.0f); }

public:
    float x, y, z;
};

// Componentwise arithmetic
Vector3 operator+ (const Vector3& lhs, const Vector3& rhs);
Vector3 operator- (const Vector3& lhs, const Vector3& rhs);
Vector3 operator* (const Vector3& lhs, const Vector3& rhs);
Vector3 operator/ (const Vector3& lhs, const Vector3& rhs);
// Scalar arithmetic
Vector3 operator* (const Vector3& lhs, float scalar);
Vector3 operator* (float scalar, const Vector3& rhs);
Vector3 operator/ (const Vector3& lhs, float scalar);
// Exact float comparison
bool operator== (const Vector3& lhs, const Vector3& rhs);
bool operator!= (const Vector3& lhs, const Vector3& rhs);

struct Vector4
{
public:
    Vector4();
    Vector4(float _x, float _y, float _z, float _w);
    Vector4(const Vector3& _xyz, float _w);

    Vector4 operator- () const;

    Vector4& operator+= (const Vector4& rhs);
    Vector4& operator-= (const Vector4& rhs);
    Vector4& operator*= (const Vector4& rhs);
    Vector4& operator/= (const Vector4& rhs);
    Vector4& operator*= (float scalar);
    Vector4& operator/= (float scalar);

public:
    // Returns the magnitude of the vector
    float Length() const;
    // Returns this vector with magnitude 1 (undefined for zero-length vectors)
    Vector4 Normalized() const;

public:
    static float Dot(const Vector4& a, const Vector4& b);

    inline static Vector4 zero() { return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
    inline static Vector4 one() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }

public:
    float x, y, z, w;
};

// Componentwise arithmetic
Vector4 operator+ (const Vector4& lhs, const Vector4& rhs);
Vector4 operator- (const Vector4& lhs, const Vector4& rhs);
Vector4 operator* (const Vector4& lhs, const Vector4& rhs);
Vector4 operator/ (const Vector4& lhs, const Vector4& rhs);
// Scalar arithmetic
Vector4 operator* (const Vector4& lhs, float scalar);
Vector4 operator* (float scalar, const Vector4& rhs);
Vector4 operator/ (const Vector4& lhs, float scalar);
// Exact float comparison
bool operator== (const Vector4& lhs, const Vector4& rhs);
bool operator!= (const Vector4& lhs, const Vector4& rhs);

///
/// MATRICES
///

struct Matrix4;

// Column-major 3x3 matrix, indexed as mat[col][row] (same layout and semantics as glm::mat3)
struct Matrix3
{
public:
    ~Matrix3() = default;
    // Initializes to identity
    Matrix3();
    Matrix3(const Matrix3& _other);
    // Diagonal matrix: Matrix3(1.0f) == identity
    explicit Matrix3(float _diagonal);
    // Upper-left 3x3 of a Matrix4
    explicit Matrix3(const Matrix4& _other);
    Matrix3(const Vector3& _c0, const Vector3& _c1, const Vector3& _c2);
    Matrix3(float _x0, float _y0, float _z0,
            float _x1, float _y1, float _z1,
            float _x2, float _y2, float _z2);

    // Column access: mat[col][row]; &mat[0][0] is 9 contiguous floats for glUniformMatrix3fv
    float* operator[] (int col) { return m[col]; }
    const float* operator[] (int col) const { return m[col]; }

    friend Matrix3 operator* (const Matrix3& lhs, const Matrix3& rhs);
    friend Vector3 operator* (const Matrix3& lhs, const Vector3& rhs);
    friend bool operator== (const Matrix3& lhs, const Matrix3& rhs);
    friend bool operator!= (const Matrix3& lhs, const Matrix3& rhs);

    Matrix3 operator* (float scalar) const;
    Matrix3& operator*= (const Matrix3& rhs);
    Matrix3& operator*= (float scalar);

public:
    inline static Matrix3 Identity() { return Matrix3(1.0f); }

    // Returns the inverse of this matrix (undefined for singular matrices)
    Matrix3 Inverse() const;

    // Post-multiplied 2D affine transforms (homogeneous coordinates)
    static Matrix3 Translate(const Matrix3& mat, const Vector2& translation);
    // Counter-clockwise rotation
    static Matrix3 Rotate(const Matrix3& mat, float angleRadians);
    static Matrix3 Scale(const Matrix3& mat, const Vector2& scale);
    static Matrix3 Ortho(float left, float right, float bottom, float top);

private:
    float m[3][3];
};

// Column-major 4x4 matrix, indexed as mat[col][row] (same layout and semantics as glm::mat4)
struct Matrix4
{
public:
    ~Matrix4() = default;
    // Initializes to identity
    Matrix4();
    Matrix4(const Matrix4& _other);
    // Diagonal matrix: Matrix4(1.0f) == identity
    explicit Matrix4(float _diagonal);
    Matrix4(const Vector4& _c0, const Vector4& _c1, const Vector4& _c2, const Vector4& _c3);
    Matrix4(float _x0, float _y0, float _z0, float _w0,
            float _x1, float _y1, float _z1, float _w1,
            float _x2, float _y2, float _z2, float _w2,
            float _x3, float _y3, float _z3, float _w3);

    // Column access: mat[col][row]; &mat[0][0] is 16 contiguous floats for glUniformMatrix4fv
    float* operator[] (int col) { return m[col]; }
    const float* operator[] (int col) const { return m[col]; }

    friend Matrix4 operator* (const Matrix4& lhs, const Matrix4& rhs);
    friend Vector4 operator* (const Matrix4& lhs, const Vector4& rhs);
    friend bool operator== (const Matrix4& lhs, const Matrix4& rhs);
    friend bool operator!= (const Matrix4& lhs, const Matrix4& rhs);

    Matrix4 operator* (float scalar) const;
    Matrix4& operator*= (const Matrix4& rhs);
    Matrix4& operator*= (float scalar);

public:
    inline static Matrix4 Identity() { return Matrix4(1.0f); }

    // Post-multiplied transforms, same semantics as glm::translate/rotate/scale/ortho
    static Matrix4 Translate(const Matrix4& mat, const Vector3& translation);
    static Matrix4 Rotate(const Matrix4& mat, float angleRadians, const Vector3& axis);
    static Matrix4 Scale(const Matrix4& mat, const Vector3& scale);
    static Matrix4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);

private:
    float m[4][4];
};

// The OpenGL upload path (&mat[0][0]) relies on tightly packed column-major storage
static_assert(sizeof(Matrix3) == 9 * sizeof(float), "Matrix3 must be 9 contiguous floats");
static_assert(sizeof(Matrix4) == 16 * sizeof(float), "Matrix4 must be 16 contiguous floats");

} // Namespace DTEngine

#endif