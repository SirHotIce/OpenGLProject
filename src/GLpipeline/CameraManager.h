//
// Created by Vin on 3/24/2025.
//

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace GLpipeline {
    class CameraManager {
    private:
        GLfloat aspectRatio;
        GLfloat nearPlane, farPlane;
        GLfloat fov;
        glm::vec3 camPosition;
        float pitch, yaw;
        glm::vec3 front;
        glm::vec3 worldUp;
        glm::vec3 right;
        glm::vec3 up;

        glm::mat4 projection;
        glm::mat4 view;

    public:
        CameraManager(GLfloat aspect_ratio, GLfloat near_plane, GLfloat far_plane, GLfloat fov, glm::vec3 world_up)
            : aspectRatio(aspect_ratio),
              nearPlane(near_plane),
              farPlane(far_plane),
              fov(fov) , worldUp(world_up){
            pitch = 180.0f;
            yaw = 90.0f;
            front = glm::vec3(0.0f, 0.0f, -1.0f); ;
            camPosition = glm::vec3(0.0f, 0.0f, 0.0f);
            right   = glm::vec3(1.0f, 0.0f, 0.0f);
            up      = glm::vec3(0.0f, 1.0f, 0.0f);

        }


        void PitchCamera(GLfloat pitch, float deltaTime);
        void YawCamera(GLfloat yaw, float deltaTime);
        void MoveCamera(GLfloat x, GLfloat y, GLfloat z, float deltaTime);
        const glm::mat4& get_projection();
        const glm::mat4& get_updated_view();
         glm::vec3& get_camera_position() ;
         glm::vec3& get_camera_front() ;

    };
}

#endif //CAMERAMANAGER_H
