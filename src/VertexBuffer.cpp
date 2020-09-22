#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const float* data, unsigned int size)
    :Buffer(data, size/sizeof(float))
{
    type = GL_ARRAY_BUFFER;
    _size = size;
    GLCall(glGenBuffers(1, &rendererId));
    GLCall(glBindBuffer(type, rendererId));
    GLCall(glBufferData(type, _size, getDataEntryPointer(), GL_STATIC_DRAW);)
}

VertexBuffer::~VertexBuffer(){
    GLCall(glDeleteBuffers(1, &rendererId));
}

void VertexBuffer::bind(){
    GLCall(glBindBuffer(type, rendererId));
}

void VertexBuffer::unbind(){
    GLCall(glBindBuffer(type, 0));
}