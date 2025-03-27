//
// Created by Vin on 3/27/2025.
//

#include "Material.h"

void GLpipeline::Material::BindMaterial(GLuint shaderProgram) {
    GLuint MaterialSpecularIntensityLocation = glGetUniformLocation(shaderProgram, "material.specularIntensity");
    GLuint MaterialShininessLocation = glGetUniformLocation(shaderProgram, "material.shininess");

    glUniform1f(MaterialSpecularIntensityLocation, specularIntensity);
    glUniform1f(MaterialShininessLocation, shininess);
}
