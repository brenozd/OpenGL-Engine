#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const Vertex *data, unsigned int count)
    : Buffer(data, count)
{
    Buffer::type = GL_ARRAY_BUFFER;
    GLCall(glGenBuffers(1, &rendererId));
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

void VertexBuffer::copyLayouts(VertexBuffer& vbo)
{
    _layouts = std::vector<attribLayout>(vbo.getLayouts());
}

void VertexBuffer::setLayout(unsigned int index, int size, unsigned int type, bool normalized,
                             unsigned int offset)
{
    attribLayout l;

    l.size = size;
    l.type = type;
    l.normalized = normalized;
    l.stride = sizeof(Vertex);
    l.entryPointer = (void*)(offset*sizeof(float));
    
    _layouts.insert(_layouts.begin() + index, l);
}