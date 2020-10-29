#ifndef ShaderProgram_h
#define ShaderProgram_h

#include <vector>
#include <GL/glew.h>
#include "Shader.h"

class ShaderProgram
{
private:
    unsigned int _programId = GL_INVALID_INDEX;
    std::unordered_map<std::string, int> _uniformsCache;

    int getUniformLocation(std::string uniform);

public:

    ShaderProgram();
    ~ShaderProgram();

    void addShader(Shader* shader);
    void removeShader(Shader* shader);
    
    void apply();

    void bind();
    void unbind();

    int setUniform1i(std::string param, int v1);
    int setUniform1f(std::string param, float v1);
    int setUniform4f(std::string param, float v1, float v2, float v3, float v4);
};

#endif