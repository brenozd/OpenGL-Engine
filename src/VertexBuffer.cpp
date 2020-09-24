#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const float *data, unsigned int count)
    : Buffer(data, count)
{
    type = GL_ARRAY_BUFFER;
    GLCall(glGenBuffers(1, &rendererId));
    bind();
    GLCall(glBufferData(type, getSize(), getDataEntryPointer(), GL_STATIC_DRAW);)
    unbind();
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &rendererId));
}

void VertexBuffer::bind()
{
    GLCall(glBindBuffer(type, rendererId));
}

void VertexBuffer::unbind()
{
    GLCall(glBindBuffer(type, 0));
}

void VertexBuffer::add(float *array, unsigned int count)
{
    Buffer::add(array, count);
    bind();
    GLCall(glBufferData(type, getSize(), getDataEntryPointer(), GL_STATIC_DRAW);)
    unbind();
}