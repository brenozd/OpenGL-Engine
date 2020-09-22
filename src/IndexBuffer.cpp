#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :Buffer(data, count)
{
    type = GL_ELEMENT_ARRAY_BUFFER;
    GLCall(glGenBuffers(1, &rendererId));
    GLCall(glBindBuffer(type, rendererId));
    GLCall(glBufferData(type, getCount() * sizeof(unsigned int), 
                        getDataEntryPointer(), GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer(){
    GLCall((glDeleteBuffers(1, &rendererId)));
}

void IndexBuffer::Bind() {
    GLCall((glBindBuffer(type, rendererId)));
}

void IndexBuffer::Unbind() {
    GLCall((glBindBuffer(type, 0)));
}
