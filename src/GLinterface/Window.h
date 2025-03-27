#include <iostream>
#include <GLFW/glfw3.h>
#ifndef WINDOW_H
#define WINDOW_H


namespace GLinterface {
    struct Window {
    public:
        GLFWwindow* window;
        GLuint windowWidth, windowHeight;
        int bWidth, bHeight;
        float cR, cG, cB, cA;
        std::string title;

    };
}
#endif