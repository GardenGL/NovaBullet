#ifndef SHADER_HPP
#define SHADER_HPP

#include <Math/glmath.hpp>
#include <string>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int ID;
    std::string m_FilePath;

public:
    Shader(const std::string &filepath);
    Shader(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc);

    ~Shader();

    void Bind() const;
    void Unbind() const;
    unsigned int GetShaderID();

    void SetBool(std::string name, bool value);
    void SetFloat(std::string name, float value);
    void SetInteger(std::string name, int value);
    void SetVector2(std::string name, const Math::vec2 &value);
    void SetVector3(std::string name, const Math::vec3 &value);
    void SetVector4(std::string name, const Math::vec4 &value);
    void SetMatrix4(std::string name, const Math::mat4x4 &matrix);
    void SetMatrix3(std::string name, const Math::mat3x3 &matrix);
    void SetColor(std::string name, Math::vec4 color);
    void HotReload();

private:
    unsigned int CompileShader(unsigned int type, const std::string &source);
    ShaderProgramSource ParseShader(const std::string &filepath);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
};

#endif