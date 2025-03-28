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
std::vector<ObjectManager*> meshList={};
std::string fsLocation="Shaders/Basic_Phong_fs.glsl";
std::string fsLocation_Toon="Shaders/Toon_Shader_fs.glsl";
std::string fsLocation_Toon_Hatched="Shaders/Hatched_Cartoon_fs.glsl";
std::string vsLocation="Shaders/MVP_vs.glsl";
void PopulateWindowData() {
    mainWindow.title="Basic Renderer";
    mainWindow.windowWidth = 2000;
    mainWindow.windowHeight = 2000;
    mainWindow.cR=1.0f;
    mainWindow.cG=1.0f;
    mainWindow.cB=1.0f;
    mainWindow.cA=1.0f;
}
void TestTransform(ObjectTransform& transform, int translationRange, int rotationRange) {
    int randomX = (std::rand() % (translationRange - (-translationRange) + 1)) + (-translationRange);
    int randomz = (std::rand() % (translationRange - (-translationRange) + 1)) + (-translationRange);
    int randomy = (std::rand() % (translationRange - (-translationRange) + 1)) + (-translationRange);
    int roty = (std::rand() % rotationRange);
    int rotz = (std::rand() % rotationRange);
    transform.set_translation( glm::vec3(randomX, randomy, randomz));//move x =5, y=1
    transform.set_rotation(glm::vec3(0.0f, roty, rotz));//rotate 90 degres in z
    transform.set_scale(glm::vec3(2.0f, 2.0f, 2.0f));//make it small
}
void CenterMesh(ObjectTransform& transform) {
    transform.set_translation( glm::vec3(0, 0, 0));//move x =5, y=1
    transform.set_rotation(glm::vec3(0.0f, 0, 0));//rotate 90 degres in z
    transform.set_scale(glm::vec3(2.0f, 2.0f, 2.0f));//make it small
}

void CreateLights(std::vector<Light>& lights) {
    Light dirLight;
    dirLight.CreateDirectionalLight(glm::vec3(0.0f,-1.0f, 0.0f), glm::vec4(1.0f), 0.35, 0.65);
    lights.push_back(dirLight);
    //
    Light pointLight;
    pointLight.CreatePointLight(glm::vec3(0.0f,0.0f, 2.0f), glm::vec4(1.0f, .5f, 0.24f, 1.0f), 0.2f,.65f, 0.1f, 0.3f , 0.5f);
    lights.push_back((pointLight));

    Light spotLight;
    spotLight.CreateSpotLight(glm::vec3(0.0f,-1.0f, 0.0f), glm::vec3(0, 3, 0), glm::vec4(1.0f, 0.85f, 0.55f, 1.0f), 0.2f,.65f, 0.1f, 0.3f , 0.5f, 60.0f);
    lights.push_back(spotLight);
}

int main() {
    PopulateWindowData();
    if (!InterfaceWindow::Initialize(mainWindow)) {
        printf("InterfaceWindow::Initialize failed\n");
        return 1;
    }

    int howManyMeshes=20;

    ShaderManager simpleShader(vsLocation, fsLocation_Toon_Hatched);
    GLuint& program= simpleShader.shader_program();
//
    //create texs
    //this is a temp soln

    std::string chickenTexLocation="Textures/chicken.png";
    Texture chickenTex(chickenTexLocation);
    chickenTex.LoadTexture();

    const char* meshFile="Meshes/chicken.fbx";
    Mesh chicken(meshFile);



    ObjectManager* obj= new ObjectManager(program,chicken, chickenTex);
    ObjectTransform &transform= obj->getTransform();
    CenterMesh(transform);

    // for (int i = 0; i < howManyMeshes; i++) {
    //     int rng= std::rand()%3;
    //     ObjectManager* obj= new ObjectManager(program,chicken, chickenTex);
    //     meshList.push_back(obj);
    // }

    GLfloat aspect_ratio= mainWindow.bWidth / mainWindow.bHeight;
    GLfloat fov= 60.0f;
    GLfloat near= 0.1f;
    GLfloat far= 1000.0f;
    CameraManager camera(aspect_ratio, near, far, fov, glm::vec3(0.0f, 1.0f, 0.0f));

    //make material
    Material shiny(1.0, 50.0f);


    //Lights
    std::vector<Light> lights;
    CreateLights(lights);

    //input system
    InputSystem* inputSystem= new InputSystem(camera, 50, 60);
    inputSystem->RegisterCallbacks(*mainWindow.window);


    // for (ObjectManager * o : meshList) {
    //     ObjectTransform &transform= o->getTransform();
    //     TestTransform(transform , 10, 180);
    //
    // }


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

        // for (ObjectManager * o  : meshList) {
        //     o->DrawObject(camera, lights, shiny);
        // }

        obj->DrawObject(camera, lights, shiny);
        glfwSwapBuffers(mainWindow.window);

    }

    // for (ObjectManager * o   : meshList) {
    //     o->DestroyObject();
    //     delete o;
    // }
    delete obj;
    delete inputSystem;
    glfwTerminate();
    simpleShader.DestroyShader();
    return 0;
}
