#ifndef VertexBuffer_h
#define VertexBuffer_h

#include "Renderer.h"
#include "Buffer.h"
#include "Buffer.cpp"

class VertexBuffer : public Buffer<float>
{
private:
    unsigned int _size = 0;

public:
    VertexBuffer(const float *data, unsigned int count);

    virtual ~VertexBuffer();

    void bind();
    void unbind();
};
#endif