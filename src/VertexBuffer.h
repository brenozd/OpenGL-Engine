#ifndef VertexBuffer_h
#define VertexBuffer_h

#include <GL/glew.h>
#include "Debugger.h"
#include "Buffer.h"
#include "Buffer.cpp"

class VertexBuffer : public Buffer<float>
{
private:
    struct Layout
    {
        int componentSize = 0;
        unsigned int type = 0;
        bool normalized = 0;
        const void *entryPointer;
    };
    Layout _layout;

public:
    VertexBuffer(const float *data, unsigned int count);
    VertexBuffer(const float *data, unsigned int count, int componentSize, unsigned int type,bool normalized);

    virtual ~VertexBuffer();

    void bind();
    void unbind();
    void apply();
    
    inline Layout layout() const {return _layout;};
    void setLayout(int componentSize, unsigned int type,bool normalized);

    
};
#endif