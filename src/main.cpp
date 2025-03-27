#include <../external/glew/include/GL/glew.h>
#include <../external/glfw/include/GLFW/glfw3.h>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

//custom
#include "GLinterface/InputSystem.h"
#include "GLinterface/InterfaceWindow.h"
#include "GLinterface/Window.h"
#include "GLpipeline/CameraManager.h"
#include "GLpipeline/ErrorHandler.h"
#include "GLpipeline/ObjectManager.h"
#include "GLpipeline/ShaderManager.h"
#include "GLpipeline/ObjectTransform.h"
#define STB_IMAGE_IMPLEMENTATION

using namespace GLinterface;
using namespace GLpipeline;

Window mainWindow;
std::vector<GLfloat> CubeVertices = {
    -0.5f, -0.5f, -0.5f, // 0: Left  Bottom Back
     0.5f, -0.5f, -0.5f,// 1: Right Bottom Back
     0.5f,  0.5f, -0.5f, // 2: Right Top    Back
    -0.5f,  0.5f, -0.5f, // 3: Left  Top    Back
    -0.5f, -0.5f,  0.5f, // 4: Left  Bottom Front
     0.5f, -0.5f,  0.5f, // 5: Right Bottom Front
     0.5f,  0.5f,  0.5f, // 6: Right Top    Front
    -0.5f,  0.5f,  0.5f  // 7: Left  Top    Front
};
std::vector<GLfloat> CubeUVs = {
   0.0f, 1.0f,// 0: Left  Bottom Back
   1.0f, 1.0f,// 1: Right Bottom Back
   1.0f, 0.0f,// 2: Right Top    Back
   0.0f, 0.0f,// 3: Left  Top    Back
   0.0f, 0.0f,// 4: Left  Bottom Front
   1.0f, 0.0f,// 5: Right Bottom Front
   1.0f, 1.0f,// 6: Right Top    Front
   0.0f, 1.0f // 7: Left  Top    Front
};
std::vector<GLuint> CubeIndices = {
    // Back face
    0, 1, 2,
    2, 3, 0,

    // Front face
    4, 5, 6,
    6, 7, 4,

    // Left faces
    0, 4, 7,
    7, 3, 0,

    // Right face
    1, 5, 6,
    6, 2, 1,

    // Bottom face
    0, 1, 5,
    5, 4, 0,

    // Top face
    3, 2, 6,
    6, 7, 3
};

std::vector<GLfloat> pyramidVerts = {
    -1.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

std::vector<GLfloat> pyramidUVs = {
    0.0f, 0.0f,
    0.5f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
};
std::vector<GLuint> pyramidIndices = {
    0,3,1,
    1,3,2,
    2,3,0,
    0,1,2
};
std::vector<ObjectManager*> meshList={};
std::string fsLocation="Shaders/traingle_fs.glsl";
std::string vsLocation="Shaders/traingle_vs.glsl";
void PopulateWindowData() {
    mainWindow.title="Basic Renderer";
    mainWindow.windowWidth = 2000;
    mainWindow.windowHeight = 2000;
    mainWindow.cR=0.5f;
    mainWindow.cG=0.5f;
    mainWindow.cB=0.5f;
    mainWindow.cA=1.0f;
}
void TestTransform(ObjectTransform& transform) {
    int randomX = (std::rand() % (10 - (-10) + 1)) + (-10);
    int randomz = (std::rand() % (10 - (-10) + 1)) + (-10);
    int randomy = (std::rand() % (10 - (-10) + 1)) + (-10);
    int roty = (std::rand() % 180);
    int rotz = (std::rand() % 180);
    transform.set_translation( glm::vec3(randomX, randomy, randomz));//move x =5, y=1
    transform.set_rotation(glm::vec3(0.0f, roty, rotz));//rotate 90 degres in z
    transform.set_scale(glm::vec3(.40f, .40f, .40f));//make it small
}

int main() {
    PopulateWindowData();
    if (!InterfaceWindow::Initialize(mainWindow)) {
        printf("InterfaceWindow::Initialize failed\n");
        return 1;
    }

    int howManyCubes=15;
    ShaderManager simpleShader(vsLocation, fsLocation);
    simpleShader.InitShader();
//
    //create texs
    //this is a temp soln

    std::string tex1Location="Textures/tex_1.jpg";
    std::string tex2Location="Textures/tex_2.jpg";
    Texture tex1(tex1Location);
    tex1.LoadTexture();
    Texture tex2(tex2Location);
    tex2.LoadTexture();





    //end

    for (int i = 0; i < howManyCubes; i++) {
        int rng= std::rand()%3;
        ObjectManager* obj= new ObjectManager(simpleShader.shader_program(), (rng>1)?pyramidVerts:CubeVertices, (rng>1)?pyramidUVs:CubeUVs, (rng>1)?pyramidIndices:CubeIndices, ((std::rand()%3)>1) ? tex1 : tex2);
        obj->PrimeObjectIndexed();
        meshList.push_back(obj);
    }

    GLfloat aspect_ratio= mainWindow.bWidth / mainWindow.bHeight;
    GLfloat fov= 60.0f;
    GLfloat near= 0.1f;
    GLfloat far= 1000.0f;
    CameraManager camera(aspect_ratio, near, far, fov, glm::vec3(0.0f, 1.0f, 0.0f));


    //make material
        Material shiny(1.0, 50.0f);

    //Lights
    std::vector<Light> lights;
    Light dirLight;
    dirLight.CreateDirectionalLight(glm::vec3(0.0f,-1.0f, 0.0f), glm::vec4(1.0f), 0.45, 0.65);
    lights.push_back(dirLight);

    //input system

    InputSystem* inputSystem= new InputSystem(camera, 50, 60);
    inputSystem->RegisterCallbacks(*mainWindow.window);
    //assign the input instance to the window

    for (ObjectManager * o : meshList) {
        ObjectTransform &transform= o->getTransform();
        TestTransform(transform);

    }


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(mainWindow.window)) {
        glfwPollEvents();
        deltaTime = glfwGetTime()-lastFrame;
        lastFrame= glfwGetTime();

        //update input time
        inputSystem->UpdateDeltaTime(deltaTime);


        glClearColor(mainWindow.cR, mainWindow.cG, mainWindow.cB, mainWindow.cA);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (ObjectManager * o  : meshList) {
            o->DrawObjectIndexed(camera, lights, shiny);
        }

        glfwSwapBuffers(mainWindow.window);

    }

    for (ObjectManager * o   : meshList) {
        o->DestroyObject();
        delete o;
    }
    delete inputSystem;
    glfwTerminate();
    simpleShader.DestroyShader();
    return 0;
}