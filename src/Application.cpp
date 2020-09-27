#include "Debugger.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <math.h>

#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

GLFWwindow *window;

int main(int argc, char *argv[])
{
    system("clear");
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

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);

    glViewport(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
#pragma endregion Initialization

    Vertex positions0[] = {
        {-0.50f,-0.50f, 0.00f, 1.00f, 0.00f, 0.00f, 1.00f},
        {-0.50f, 0.00f, 0.00f, 0.00f, 1.00f, 0.00f, 1.00f},
        { 0.00f,-0.50f, 0.00f, 0.00f, 0.00f, 1.00f, 1.00f},
        { 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 1.00f}};

    Vertex positions1[] = {
        {0.25f, 0.25f, 0, 1.00f, 0.00f, 0.00f, 1.0f},
        {0.25f, 0.75f, 0, 0.00f, 1.00f, 0.00f, 1.0f},
        {0.75f, 0.25f, 0, 0.00f, 0.00f, 1.00f, 1.0f}};

    unsigned int indices0[] = {
        0, 1, 2,
        2, 3, 1};

    unsigned int indices1[] = {
        0, 1, 2};

    VertexArray vao0 = VertexArray();

    IndexBuffer ibo0(indices0, 6);
    ibo0.apply();

    VertexBuffer vbo0 = VertexBuffer(positions0, 4);
    
    vbo0.setLayout(0, 3, GL_FLOAT, GL_FALSE, 0);
    vbo0.setLayout(1, 4, GL_FLOAT, GL_FALSE, 3);
    vbo0.apply();

    vao0.addBuffer(vbo0);
    vao0.linkIbo(&ibo0);

    VertexArray vao1 = VertexArray();

    IndexBuffer ibo1(indices1, 6);
    ibo1.apply();

    VertexBuffer vbo1 = VertexBuffer(positions1, 4);
    vbo1.setLayout(0, 3, GL_FLOAT, GL_FALSE, 0);
    vbo1.setLayout(1, 4, GL_FLOAT, GL_FALSE, 3);
    vbo1.apply();

    vao1.addBuffer(vbo1);
    vao1.linkIbo(&ibo1);

    Shader vertex = Shader("res/shaders/basic.vertex");
    Shader fragment = Shader("res/shaders/basic.fragment");

    ShaderProgram shaderProgram = ShaderProgram();
    shaderProgram.addShader(&vertex);
    shaderProgram.addShader(&fragment);
    shaderProgram.apply();

    float c = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        Renderer::draw(vao1, shaderProgram);
        Renderer::draw(vao0, shaderProgram);

        

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
