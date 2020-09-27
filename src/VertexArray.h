#ifndef VertexArray_h
#define VertexArray_h

#include <GL/glew.h>
#include "Debugger.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
private:
    unsigned int _rendererId = 0;
    IndexBuffer* _ibo;

public:
    VertexArray();

    ~VertexArray();

    void bind();
    void unbind();

    void addBuffer(VertexBuffer& vbo);
    void linkIbo(IndexBuffer* ibo);
    inline IndexBuffer getIbo() const {return *_ibo;};
};

#endif