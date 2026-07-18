#include "Shader.hpp"

#include <DTEngine/Utils.hpp>

#include "glad/glad.h"
#include <stdexcept>

using namespace DTEngine;

Shader::~Shader()
{
    glDeleteProgram(program);
}

Shader::Shader(
    const std::string& vertexFile, const char* vertexSource, 
    const std::string& fragmentFile, const char* fragmentSource)
{
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::runtime_error("Error compiling vertex shader from file: " + std::string(vertexFile));
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::runtime_error("Error compiling fragment shader from file: " + std::string(fragmentFile));
    }

    // link shaders
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // check for linking errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        throw std::runtime_error("Error linking shader program from vertex " + std::string(vertexFile) + " and fragment " + std::string(fragmentFile));
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Default shader values
    Bind();
    SetVec4("baseColor", Vector4(1.0f, 0.741f, 0.75f, 1.0f));
    SetInt("tex", 0);
    Unbind();
}

void Shader::Bind()
{
    glUseProgram(program);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

// ------------------------------------------------------------------------
void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetUInt(const std::string& name, unsigned int value) const
{
    glUniform1ui(glGetUniformLocation(program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetVec4(const std::string& name, const Vector4& value) const
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z, value.w);
}
void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMat3(const std::string& name, const Matrix3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat4(const std::string& name, const Matrix4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}