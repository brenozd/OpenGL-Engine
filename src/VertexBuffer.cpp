#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const float *data, unsigned int count)
    : Buffer(data, count)
{
    Buffer::type = GL_ARRAY_BUFFER;
    GLCall(glGenBuffers(1, &rendererId));
}

VertexBuffer::VertexBuffer(const float *data, unsigned int count, 
                           int componentSize, unsigned int type, bool normalized)
    : Buffer(data, count)
{
    Buffer::type = GL_ARRAY_BUFFER;
    GLCall(glGenBuffers(1, &rendererId));
    setLayout(componentSize, type, normalized);
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

void VertexBuffer::apply()
{
    bind();
    GLCall(glBufferData(type, getSize(), getDataEntryPointer(), GL_STATIC_DRAW);)
    unbind();
}

void VertexBuffer::setLayout(int componentSize, unsigned int type, bool normalized)
{
    _layout.componentSize = componentSize;
    _layout.type = type;
    _layout.normalized = normalized;
    _layout.entryPointer = getDataEntryPointer();
}