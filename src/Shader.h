#ifndef Shader_h
#define Shader_h

#include <GL/glew.h>
#include "Debugger.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <unordered_map>
#include <vector>

enum class ShaderType
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1,
    COMPUTE = 2,
};

struct ShaderAttrib
{
    unsigned int id;
    ShaderType type;
    std::string source;
};

class Shader
{
private:
    ShaderAttrib _shaderAttrib;

    ShaderAttrib parseShader(std::string path);

    unsigned int compileShader(ShaderAttrib shaderProgram);
    
public:
    Shader(std::string path);
    Shader();
    ~Shader();

    

    inline ShaderAttrib getShaderAttrib() {return _shaderAttrib;};
};

#endif