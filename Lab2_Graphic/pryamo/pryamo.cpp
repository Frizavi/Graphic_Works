// Распутин Захар ЭВМб-23-1
// 20 Вариант

#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shaders.h" //Библиотека для работы с шейдерами//

GLfloat points[] = { 0.8, 0.5, 0.0,
                    -0.8, 0.5, 0.0,
                    -0.8, -0.5, 0.0,
                     0.8, -0.5, 0.0
};
GLuint index[] = { 0, 1, 2, 3 };

int main() {

    printf("Hello World!\n");

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3.\n");
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "52Rectangle52", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3.\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
    glEnableVertexAttribArray(0);


                                                //Загрузка шейдеров//
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    GLuint shaderProgram = loadShader("shader/vertex_shader.glsl", "shader/fragment_shader.glsl");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0, 1.0, 1.0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        float timeValue = glfwGetTime();
        float red = (sin(timeValue) / 2.0f) + 0.5f;
        float green = (sin(timeValue + 1.0f) / 2.0f) + 0.5f;
        float blue = (sin(timeValue + 2.0f) / 2.0f) + 0.5f;

        setUniform4f(shaderProgram, "outColor", red, green, blue, 1.0f);

        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}