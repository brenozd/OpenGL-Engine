#ifndef Vertex_h
#define Vertex_h

#define COLOR_STRIDE 3*sizeof(float)

struct Vertex{
    float x = 0;
    float y = 0;
    float z = 0;

    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;
};

#endif