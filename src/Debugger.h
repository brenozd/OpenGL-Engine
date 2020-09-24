#ifndef Debugger_h
#define Debugger_h

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>

#pragma region Macros
#define BREAKPOINT asm("int $3")

#define ASSERT(x) \
    if (!(x))     \
        BREAKPOINT;

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#pragma endregion Macros

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

unsigned long int getExecTime(void* func);

void testTriangle();

#endif