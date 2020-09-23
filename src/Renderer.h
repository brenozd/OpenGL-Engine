#ifndef Renderer_h
#define Renderer_h

#include <GL/glew.h>

#define BREAKPOINT asm("int $3")

#define ASSERT(x) \
    if (!(x))     \
        BREAKPOINT;

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))



void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

void testTriangle();
#endif