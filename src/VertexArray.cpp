#ifndef VertexArray_cpp
#define VertexArray_cpp

#include "VertexArray.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &_rendererId));
}

VertexArray::VertexArray(Buffer<float> buff)
{
    GLCall(glGenVertexArrays(1, &_rendererId));
    addBuffer(buff);
}

//TO FIX
VertexArray::VertexArray(float *buff, unsigned int size, int componentSize, unsigned int type, bool normalized)
{
    GLCall(glGenVertexArrays(1, &_rendererId));
    VertexBuffer vbo = VertexBuffer(buff, size);
    vbo.setLayout(componentSize, type, normalized);
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

void VertexArray::addBuffer(Buffer<float> buff)
{
    bind();
    GLCall(glBindBuffer(buff.type, buff.rendererId));

    unsigned int entryPointer = 0;
    uint32_t stride = (buff.layout.componentSize * sizeof(float));
    for (unsigned int i = 0; i < buff.getCount(); i++)
    {
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, buff.layout.componentSize, buff.layout.type, buff.layout.normalized,
                                     stride, (void *)entryPointer));
        entryPointer += stride;
    }
}

#endif