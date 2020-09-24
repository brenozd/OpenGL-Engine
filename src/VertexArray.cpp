#include "VertexArray.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &_rendererId));
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

    unsigned int entryPointer = _elementsInBuffer * sizeof(float);
    uint32_t stride = (vbo.layout().componentSize * sizeof(float));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, vbo.layout().componentSize, vbo.layout().type, vbo.layout().normalized,
                                 stride, (void *)entryPointer));
    _elementsInBuffer += vbo.getCount();
    vbo.unbind();
    unbind();
}

void VertexArray::linkIbo(IndexBuffer* ibo)
{
    _ibo = ibo;
}