#ifndef VertexArray_h
#define VertexArray_h

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
private:
    unsigned int _rendererId = 0;

public:
    VertexArray();
    VertexArray(VertexBuffer& vbo);

    ~VertexArray();

    void bind();
    void unbind();

    void addBuffer(VertexBuffer& vbo);
};

#endif