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
    //Initialization
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

    if (GLEW_OK != glewInit())
    {
        printf("GLEW not initialized...");
        return -1;
    }

    std::cout << "[OpenGL Version] " << std::endl
              << glGetString(GL_VERSION) << std::endl;

    glewExperimental = true;

    glViewport(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);

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
        2, 3, 1};

    VertexBuffer vbo0(positions0, 8 * sizeof(float));
    vbo0.setLayout(2, GL_FLOAT, GL_FALSE);

    VertexBuffer vbo1(positions1, 8 * sizeof(float));
    vbo1.setLayout(2, GL_FLOAT, GL_FALSE);

    vbo0.bind();
    vbo1.bind();

    IndexBuffer ibo(indices, 6);
    ibo.bind();

    Shader::bind("res/shaders/basic.vertex");
    Shader fragment = Shader("res/shaders/basic.fragment");
    fragment.bind();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        fragment.setUniform4f("u_Color", 0.3f, 0.3f, 0.3f, 1.0f);

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}