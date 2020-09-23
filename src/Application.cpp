#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "VertexArray.h"

#include <GLFW/glfw3.h>

#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

GLFWwindow *window;

int main(int argc, char *argv[])
{
#pragma region Initialization
    if (!glfwInit())
    {
        printf("GLFW not initialized...");
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(SCREEN_SIZE_X, SCREEN_SIZE_Y, "OpenGL", NULL, NULL);

    if (!window)
    {
        printf("Window not initialized...");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = true;

    if (GLEW_OK != glewInit())
    {
        printf("GLEW not initialized...");
        return -1;
    }

    std::cout << "[OpenGL Version] " << std::endl
              << glGetString(GL_VERSION) << std::endl;

    glViewport(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
#pragma endregion Initialization

    float positions0[] = {
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,
        -0.5f,
        0.0f,
        0.0f,
    };

    float positions1[] = {
        0.25f,
        0.25f,
        0.25f,
        0.75f,
        0.75f,
        0.25f,
        0.75f,
        0.75f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 1,
        4, 5, 6,
        6, 7, 4};

    VertexArray vao0 = VertexArray();

    VertexBuffer vbo0 = VertexBuffer(positions0, 8);
    vbo0.setLayout(2, GL_FLOAT, GL_FALSE);

    IndexBuffer ibo(indices, 6);

    vao0.addBuffer(vbo0);

    Shader::bind("res/shaders/basic.vertex");
    Shader fragment = Shader("res/shaders/basic.fragment");
    fragment.bind();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        fragment.setUniform4f("u_Color", 0.3f, 0.3f, 0.3f, 1.0f);

        vao0.bind();
        ibo.bind();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, ibo.getDataEntryPointer()));
        vao0.unbind();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
