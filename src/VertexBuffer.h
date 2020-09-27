#ifndef VertexBuffer_h
#define VertexBuffer_h

#include <vector>

#include <GL/glew.h>
#include "Debugger.h"
#include "Buffer.h"
#include "Buffer.cpp"
#include "Vertex.h"

struct attribLayout
{
    int size;
    unsigned int type;
    bool normalized;
    uint32_t stride;
    void* entryPointer;
    unsigned int offset;
};

class VertexBuffer : public Buffer<Vertex>
{
private:
    std::vector<attribLayout> _layouts;

public:
    VertexBuffer(const Vertex *data, unsigned int count);

    virtual ~VertexBuffer();

    void bind();
    void unbind();
    void apply();

    inline std::vector<attribLayout>  getLayouts() const { return _layouts;};
    void copyLayouts(VertexBuffer& vbo);

    void setLayout(unsigned int index, int size, unsigned int type, bool normalized, unsigned int offset);
};
#endif