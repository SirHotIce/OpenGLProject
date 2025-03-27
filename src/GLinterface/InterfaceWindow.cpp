//
// Created by Vin on 3/23/2025.
//

#include "InterfaceWindow.h"
using namespace GLinterface;

void InterfaceWindow::SetupHints() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}
bool InterfaceWindow::CreateWindow(Window &window) {
    window.window=glfwCreateWindow(window.windowWidth, window.windowHeight, window.title.c_str(), NULL, NULL);
    if (&window.window == NULL) {
        return false;
    }
    glfwGetFramebufferSize(window.window, &window.bWidth, &window.bHeight);
    glfwMakeContextCurrent(window.window);
    glViewport(0, 0, window.bWidth, window.bHeight);
    return true;
}

bool InterfaceWindow::Initialize(Window &window) {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        glfwTerminate();
        return false;
    }
    SetupHints();
    if (!CreateWindow(window)) {
        printf("Failed to create window\n");
        glfwDestroyWindow(window.window);
        glfwTerminate();
        return false;
    }
    if (glewInit()!= GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        glfwDestroyWindow(window.window);
        glfwTerminate();
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    return true;
}

