#include "Renderer.h"

void Renderer::draw(VertexArray &vao, ShaderProgram shaderP)
{
    
    vao.bind();
    shaderP.bind();
    GLCall(glDrawElements(GL_TRIANGLES, vao.getIbo().getCount(), GL_UNSIGNED_INT,
                          vao.getIbo().getDataEntryPointer()))
}