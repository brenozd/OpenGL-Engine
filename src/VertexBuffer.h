#ifndef VertexBuffer_h
#define VertexBuffer_h

#include "Renderer.h"
#include "Buffer.h"
#include "Buffer.cpp"

class VertexBuffer : public Buffer<float>
{
public:
    VertexBuffer(const float *data, unsigned int count);

    virtual ~VertexBuffer();

    void bind();
    void unbind();

    void add(float *array, unsigned int count);
};
#endif