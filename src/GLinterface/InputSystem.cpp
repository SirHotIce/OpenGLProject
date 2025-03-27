//
// Created by Vin on 3/25/2025.
//

#include "InputSystem.h"

void GLinterface::InputSystem::
keyBoardInputs_Callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    auto* instance=static_cast<InputSystem *>(glfwGetWindowUserPointer(window));//derefering the window user pouinter that links an instance of the inputsystem to the current window, basically this instance is linked to this window, just an "easy" way to get the instance that stores othe members
    if (instance!=nullptr) {
        instance->HandleCameraTranslations(key);
    }
}
void GLinterface::InputSystem::mouseMove_Callback(GLFWwindow *window, double x, double y) {
    auto* instance= static_cast<InputSystem *>(glfwGetWindowUserPointer(window));
    if (instance!=nullptr) {
        instance->HandleCameraRotations(x, y);
    }
}
void GLinterface::InputSystem::RegisterCallbacks(GLFWwindow& window) {
    glfwSetKeyCallback(&window, keyBoardInputs_Callback);
    glfwSetCursorPosCallback(&window, mouseMove_Callback);
    if (this!=nullptr)
        glfwSetWindowUserPointer(&window, this);
}

void GLinterface::InputSystem::UpdateDeltaTime(double dt) {
    deltaTime=dt;
}



void GLinterface::InputSystem::HandleCameraTranslations(int key) {
    switch (key) {
        case GLFW_KEY_W:
            camera->MoveCamera(0, 0, movementSpeed, deltaTime);
            break;
        case GLFW_KEY_S:
            camera->MoveCamera(0, 0, -movementSpeed, deltaTime);
            break;
        case GLFW_KEY_A:
            camera->MoveCamera(-movementSpeed, 0, 0, deltaTime);
            break;
        case GLFW_KEY_D:
            camera->MoveCamera(movementSpeed, 0, 0, deltaTime);
            break;
    }
}

void GLinterface::InputSystem::HandleCameraRotations(double x, double y) {
    double xDiff= x-previousMouseX;
    double yDiff= y-previousMouseY;
    previousMouseX=x;
    previousMouseY=y;
    camera->PitchCamera(-yDiff*rotationSpeed, deltaTime);
    camera->YawCamera(-xDiff*rotationSpeed, deltaTime);

}
