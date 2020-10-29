#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    _programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteShader(_programId);
}

void ShaderProgram::addShader(Shader *shader)
{
    glAttachShader(_programId, shader->getShaderAttrib().id);
}

void ShaderProgram::removeShader(Shader *shader)
{
    glDetachShader(_programId, shader->getShaderAttrib().id);
}

void ShaderProgram::apply()
{
    glLinkProgram(_programId);

    int isLinked = 0;
    glGetProgramiv(_programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(_programId, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(_programId);

        std::cout << "[ERROR] Linking Shader\n"
                  << infoLog.data() << "\n";
        return;
    }

    glValidateProgram(_programId);
}

void ShaderProgram::bind()
{
    glUseProgram(_programId);
}

void ShaderProgram::unbind()
{
    glUseProgram(0);
}

int ShaderProgram::getUniformLocation(std::string uniform)
{
    if (_uniformsCache.find(uniform) != _uniformsCache.end())
        return _uniformsCache[uniform];
    else
    {
        int location = glGetUniformLocation(_programId, uniform.c_str());
        _uniformsCache[uniform] = location;
        return location;
    }
}

int ShaderProgram::setUniform1i(std::string param, int v1)
{
    bind();
    if (_programId == GL_INVALID_INDEX)
        return 0;
    GLCall(glUniform1i(getUniformLocation(param), v1));
    unbind();
    return 1;
}

int ShaderProgram::setUniform1f(std::string param, float v1)
{
    bind();
    if (_programId == GL_INVALID_INDEX)
        return 0;
    GLCall(glUniform1f(getUniformLocation(param), v1));
    unbind();
    return 1;
}

int ShaderProgram::setUniform4f(std::string param, float v1, float v2, float v3, float v4)
{
    bind();
    if (_programId == GL_INVALID_INDEX)
        return 0;
    GLCall(glUniform4f(getUniformLocation(param), v1, v2, v3, v4));
    unbind();
    return 1;
}