//
// Created by Vin on 3/23/2025.
//

#ifndef INTERFACEWINDOW_H
#define INTERFACEWINDOW_H



#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"

namespace GLinterface {
    class InterfaceWindow {
    private:
        static void SetupHints();
        static bool CreateWindow(Window &window);
    public:
        static bool Initialize(Window &window);


    };
}




#endif //INTERFACEWINDOW_H
