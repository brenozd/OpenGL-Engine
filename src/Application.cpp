#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "VertexArray.h"

#include <GLFW/glfw3.h>

#include "Vertex.h"

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
    };

    unsigned int indices0[] = {
        0, 1, 2,
        2, 3, 1};

    unsigned int indices1[] = {
        0,1,2};

    VertexArray vao0 = VertexArray();

    IndexBuffer ibo0(indices0, 6);
    ibo0.apply();

    VertexBuffer vbo0 = VertexBuffer(positions0, 8, 2, GL_FLOAT, GL_FALSE);
    vbo0.apply();

    vao0.addBuffer(vbo0);
    vao0.linkIbo(&ibo0);

    VertexArray vao1 = VertexArray();

    IndexBuffer ibo1(indices1, 6);
    ibo1.apply();

    VertexBuffer vbo1 = VertexBuffer(positions1, 8, 2, GL_FLOAT, GL_FALSE);
    vbo1.apply();

    vao1.addBuffer(vbo1);
    vao1.linkIbo(&ibo1);

    Shader::bind("res/shaders/basic.vertex");
    Shader fragment = Shader("res/shaders/basic.fragment");
    fragment.bind();
    float c = 0.0f, s = -0.05f;

    std::cout << COLOR_STRIDE << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        fragment.setUniform4f("u_Color", c, 0.3f, 0.3f, 1.0f);
        Renderer::draw(vao0, fragment);
        fragment.setUniform4f("u_Color", 0.3f, c, 0.3f, 1.0f);
        Renderer::draw(vao1, fragment);

        if(c > 1 || c < 0)
            s *= -1.0f;
        c += s;

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
