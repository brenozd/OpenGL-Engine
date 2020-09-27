#ifndef Renderer_h
#define Renderer_h

#include <GL/glew.h>
#include "VertexArray.h"
#include "ShaderProgram.h"

class Renderer
{
private:
    std::vector<ShaderAttrib> _shaders;

public:
    static void draw(VertexArray &vao, ShaderProgram shaderP);
};

#endif