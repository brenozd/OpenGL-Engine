#ifndef IndexBuffer_h
#define IndexBuffer_h

#include "Renderer.h"
#include "Buffer.h"
#include "Buffer.cpp"

class IndexBuffer  : public Buffer<unsigned int>
{public:

    IndexBuffer(const unsigned int* data, unsigned int size);
    virtual ~IndexBuffer();

    void Bind();
    void Unbind();
};

#endif