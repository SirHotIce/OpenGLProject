//
// Created by Vin on 3/24/2025.
//

#include "CameraManager.h"
#include <iostream>
#include <ostream>

const glm::mat4& GLpipeline::CameraManager::get_projection() {
    projection= glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    return projection;
}


void GLpipeline::CameraManager::PitchCamera(GLfloat p, float deltaTime) {
    pitch+=(p*deltaTime);
    if (glm::abs(pitch)>360)
        pitch=0;
}

void GLpipeline::CameraManager::YawCamera(GLfloat y, float deltaTime) {
    yaw-=(y*deltaTime);
    if (glm::abs(yaw)>360)
        yaw=0;
}

void GLpipeline::CameraManager::MoveCamera(GLfloat x, GLfloat y, GLfloat z, float deltaTime) {
    camPosition += front*z*deltaTime;
    camPosition += right*x*deltaTime;

}
const glm::mat4 & GLpipeline::CameraManager::get_updated_view() {

    front.x= glm::cos(glm::radians(pitch))* glm::cos(glm::radians(yaw));
    front.y= glm::sin(glm::radians(pitch));
    front.z= glm::sin(glm::radians(yaw))* glm::cos(glm::radians(pitch));

    front= glm::normalize(front);

    right= glm::cross(front, worldUp);
    right= glm::normalize(right);
    up= glm::cross(right, front);
    up= glm::normalize(up);

    view = glm::lookAt(camPosition, camPosition+front, up);//not just front, we want front of the camera not just the front vector we have to  make it relative

    return view;
}

 glm::vec3& GLpipeline::CameraManager::get_camera_position() {
    return camPosition;
}

 glm::vec3 & GLpipeline::CameraManager::get_camera_front()  {
    return front;
}

float & GLpipeline::CameraManager::getFarPlane() {
    return farPlane;
}

float & GLpipeline::CameraManager::getNearPlane() {
    return nearPlane;
}
