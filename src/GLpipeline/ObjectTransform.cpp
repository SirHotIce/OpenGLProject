//
// Created by Vin on 3/24/2025.
//

#include "ObjectTransform.h"

GLpipeline::ObjectTransform::ObjectTransform() {//initialize by creating identity matrices
    set_translation(glm::vec3(0.0f, 0.0f, 0.0f));
    set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
    set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::mat4(1.0f);
}
//not returning the right model
 const glm::mat4& GLpipeline::ObjectTransform::get_model(){
    //make a trs
    model= glm::mat4(1.0f);//needs to reset to an identity every run
    model = glm::translate(model, translation);
    model= glm::rotate(model, rotation.x*radianConverter, glm::vec3(1.0f, 0.0f, 0.0f));//x-axis
    model=glm::rotate(model, rotation.y*radianConverter, glm::vec3(0.0f, 1.0f, 0.0f));//y-axis
    model=glm::rotate(model, rotation.z*radianConverter, glm::vec3(0.0f, 0.0f, 1.0f));//z-axis
    model=glm::scale(model, scale);


    return model;
}
