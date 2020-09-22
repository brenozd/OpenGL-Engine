#ifndef VertexArray_h
#define VertexArray_h

#include "Renderer.h"
#include "VertexBuffer.h"

class VertexArray
{
private:
    unsigned int _rendererId = 0;

public:
    VertexArray();

    VertexArray(Buffer<float> buff);

    VertexArray(float* buff, unsigned int size, int componentSize, unsigned int type, bool normalized);

    ~VertexArray();

    void bind();
    void unbind();

    void addBuffer(Buffer<float> buff);
};

#endif