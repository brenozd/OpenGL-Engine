#ifndef Shader_h
#define Shader_h

#include <GL/glew.h>
#include "Debugger.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string.h>

enum class ShaderType
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1,
    COMPUTE = 2,
};

struct ShaderProgram
{
    unsigned int id;
    ShaderType type;
    std::string source;
};

class Shader
{
private:
    unsigned int _rendererId;
    ShaderProgram _shaderProgram;

    static ShaderProgram parseShader(std::string path);

    static unsigned int compileShader(ShaderProgram shaderProgram);

public:
    Shader(std::string path);
    ~Shader();

    void bind();
    
    static unsigned int bind(std::string path);
    static void unbind();
    int setUniform4f(std::string param, float v1, float v2, float v3, float v4);

    inline unsigned int GetShaderId() {return _rendererId;};
    inline ShaderType GetShaderType() {return _shaderProgram.type;};
    inline std::string GetShaderSource() {return _shaderProgram.source;};
};

#endif