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
/// MISC
/// 

typedef uint32_t LayerMask;

// Mask matching every layer
constexpr LayerMask LAYER_MASK_ALL = ~0u;

///
/// MISC
/// 

struct Vector2
{
public:
    ~Vector2() = default;
    Vector2();
    Vector2(const Vector2& _other);
    Vector2(float _x, float _y);

    friend Vector2 operator+ (const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator* (const Vector2& lhs, const Vector2& rhs);

    Vector2 operator* (float scalar) const {
       return Vector2(this->x * scalar, this->y * scalar);
    }

    Vector2 operator- () const {
       return Vector2(-this->x, -this->y);
    }

    Vector2& operator+= (const Vector2& rhs) {
       this->x += rhs.x;
       this->y += rhs.y;

       return *this;
    }

    Vector2& operator*= (const Vector2& rhs) {
       this->x *= rhs.x;
       this->y *= rhs.y;

       return *this;
    }

public:
    // Rotates a vector counter-clockwise around the origin
    void Rotate(float degrees);

public:
    // Calculates the distance between two vectors
    static float Distance(const Vector2& a, const Vector2& b);

    inline static Vector2 zero() { return Vector2(0.0f, 0.0f); }
    inline static Vector2 one() { return Vector2(1.0f, 1.0f); }
    inline static Vector2 right() { return Vector2(1.0f, 0.0f); }
    inline static Vector2 up() { return Vector2(0.0f, 1.0f); }

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
    // Calculates the distance between two vectors
    static float Distance(const Vector3& a, const Vector3& b);

public:
    float z;
};

struct Vector4 : public Vector3
{
public:
    ~Vector4() = default;
    Vector4();
    Vector4(const Vector2& _other);
    Vector4(const Vector3& _other);
    Vector4(const Vector4& _other);
    Vector4(float _x, float _y, float _z, float _w);

public:
    float w;
};

}

#endif