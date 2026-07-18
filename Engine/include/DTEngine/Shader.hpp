#ifndef DTENGINE_SHADER_H
#define DTENGINE_SHADER_H

#include <string>

namespace DTEngine
{

struct Vector4;
struct Matrix3;
struct Matrix4;

class Shader
{
friend class RenderingSystem;
friend class SpriteRenderer;

public:
    ~Shader();
    Shader(
        const std::string& vertexFile, const char* vertexSource, 
        const std::string& fragmentFile, const char* fragmentSource);

    void SetInt(const std::string& name, int value) const;
    void SetUInt(const std::string& name, unsigned int value) const;
    void SetVec4(const std::string& name, const Vector4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat3(const std::string& name, const Matrix3& mat) const;
    void SetMat4(const std::string& name, const Matrix4& mat) const;

private:
    void Bind();
    void Unbind();

private:
    unsigned int program;

};

}

#endif