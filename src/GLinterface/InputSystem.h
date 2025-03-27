//
// Created by Vin on 3/25/2025.
//

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include "InterfaceWindow.h"
#include "../GLpipeline/CameraManager.h"
#include <glfw/glfw3.h>


namespace GLinterface {
    class InputSystem {
    private:
        GLpipeline::CameraManager* camera;
        float movementSpeed, rotationSpeed;
        double deltaTime;
        double previousMouseX, previousMouseY;
        float xPos=0, yPos=0, zPos=0;

        public:
        InputSystem(GLpipeline::CameraManager& cam, float movement_speed, float rotation_speed): camera(&cam), movementSpeed(movement_speed), rotationSpeed(rotation_speed) {
        };

        void HandleCameraTranslations(int key);
        void HandleCameraRotations(double x, double y);

        void UpdateDeltaTime(double dt);

        static void keyBoardInputs_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void mouseMove_Callback(GLFWwindow* window, double x, double y);

        void RegisterCallbacks(GLFWwindow& window);


    };
}


#endif //INPUTSYSTEM_H
