#include "VertexArray.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &_rendererId));
}

VertexArray::VertexArray(VertexBuffer &vbo)
{
    GLCall(glGenVertexArrays(1, &_rendererId));
    addBuffer(vbo);
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &_rendererId));
}

void VertexArray::bind()
{
    GLCall(glBindVertexArray(_rendererId));
}

void VertexArray::unbind()
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(VertexBuffer &vbo)
{
    bind();
    vbo.bind();

    unsigned int entryPointer = 0;

    uint32_t stride = (vbo.layout.componentSize * sizeof(float));
    for (unsigned int i = 0; i < vbo.getCount(); i++)
    {
        GLCall(glEnableVertexAttribArray(i));
        
        GLCall(glVertexAttribPointer(i, vbo.layout.componentSize, vbo.layout.type, vbo.layout.normalized,
                                     stride, (void *)entryPointer));
        entryPointer += stride;
    }
}