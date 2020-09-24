#ifndef IndexBuffer_h
#define IndexBuffer_h

#include <GL/glew.h>
#include "Debugger.h"
#include "Buffer.h"
#include "Buffer.cpp"

class IndexBuffer  : public Buffer<unsigned int>
{public:

    IndexBuffer(const unsigned int* data, unsigned int count);
    virtual ~IndexBuffer();

    void bind();
    void unbind();
    void apply();
    
};

#endif