//Распутин Захар ЭВМб-23-1//
//20 Вариант//


#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
    printf("Hello World!\n");

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3.\n");
        return 1;
    }

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "52Rectangle52", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3.\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0, 1.0, 1.0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        //В 20 варианте стоит белый прямоугольник на белом фоне, я сделал другого цвета, чтобы было заметно//
        glColor3f(0.9, 0.8, 0.9);

        glBegin(GL_QUADS);
        glVertex2f(0.8, 0.5);
        glVertex2f(-0.8, 0.5);
        glVertex2f(-0.8, -0.5);
        glVertex2f(0.8, -0.5);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
