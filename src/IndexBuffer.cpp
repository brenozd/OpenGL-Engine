#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :Buffer(data, count)
{
    type = GL_ELEMENT_ARRAY_BUFFER;
    GLCall(glGenBuffers(1, &rendererId));
}

IndexBuffer::~IndexBuffer(){
    GLCall((glDeleteBuffers(1, &rendererId)));
}

void IndexBuffer::bind() {
    GLCall((glBindBuffer(type, rendererId)));
}

void IndexBuffer::unbind() {
    GLCall((glBindBuffer(type, 0)));
}

void IndexBuffer::apply()
{
    bind();
    GLCall(glBufferData(type, getSize(), getDataEntryPointer(), GL_STATIC_DRAW);)
    unbind();
}
