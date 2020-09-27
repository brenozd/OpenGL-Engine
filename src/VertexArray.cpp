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

    std::vector<attribLayout> elements = vbo.getLayouts();
    unsigned int elementsInBuffer = elements.size();
    
    for (int i = 0; i < elementsInBuffer; i++)
    {
        
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, elements[i].size, elements[i].type, elements[i].normalized,
                                     elements[i].stride, elements[i].entryPointer));
    }

    vbo.unbind();
    unbind();
}

void VertexArray::linkIbo(IndexBuffer *ibo)
{
    _ibo = ibo;
}