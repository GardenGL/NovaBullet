#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

void Shader::SetBool(std::string name, bool value) { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
void Shader::SetFloat(std::string name, float value) { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::SetInteger(std::string name, int value) { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::SetVector2(std::string name, const Math::vec2 &value) { glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y); }
void Shader::SetVector3(std::string name, const Math::vec3 &value) { glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z); }
void Shader::SetVector4(std::string name, const Math::vec4 &value) { glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w); }
void Shader::SetMatrix4(std::string name, const Math::mat4x4 &matrix) { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false, matrix.m); }
void Shader::SetMatrix3(std::string name, const Math::mat3x3 &matrix) { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false, matrix.m); }
void Shader::SetColor(std::string name, Math::vec4 color) { glUniform4f(glGetUniformLocation(ID, name.c_str()), (float)color.r / (float)255.0f, color.g / 255.0f, (float)color.b / 255.0f, (float)color.a / 255.0f); }

Shader::Shader(const std::string &filepath)
{
    ShaderProgramSource source = ParseShader(filepath);
    ID = CreateShader(source.VertexSource, source.FragmentSource);
    m_FilePath = filepath;
}

Shader::Shader(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc)
{
    ID = CreateShader(vertexShaderSrc, fragmentShaderSrc);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
        COMPUTE = 2
    };

    std::string line;
    std::stringstream ss[3];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLint success;
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const
{
    glUseProgram(ID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

unsigned int Shader::GetShaderID()
{
    return ID;
}

void Shader::HotReload()
{
    glDeleteProgram(ID);
    ShaderProgramSource source = ParseShader(m_FilePath);
    ID = CreateShader(source.VertexSource, source.FragmentSource);
}
