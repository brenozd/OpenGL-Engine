#ifndef Renderer_h
#define Renderer_h

#include <GL/glew.h>
#include "VertexArray.h"
#include "Shader.h"
class Renderer
{
public:
    static void draw(VertexArray &vao, Shader frgs);
};

#endif