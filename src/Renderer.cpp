#include "Renderer.h"

void Renderer::draw(VertexArray &vao, Shader frgs)
{
    vao.bind();
    frgs.bind();

    GLCall(glDrawElements(GL_TRIANGLES, vao.getIbo().getCount(), GL_UNSIGNED_INT, 
                          vao.getIbo().getDataEntryPointer()))
}