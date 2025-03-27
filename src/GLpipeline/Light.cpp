//
// Created by Vin on 3/27/2025.
//

#include "Light.h"



void GLpipeline::Light::CreateDirectionalLight(glm::vec3 light_dir, glm::vec4 light_color, float ambient_strength,
                                               float diffuse_strength) {
    lightType=0;
    lightDir = glm::normalize(light_dir);
    lightColor= light_color;
    ambientStrength = ambient_strength;
    diffuseStrength = diffuse_strength;
    lightPos = glm::vec3(0, 0, 0);
    lightAttenuation=0.0f;
    cutOffAngle= 0.0f;
}

void GLpipeline::Light::CreatePointLight(glm::vec3 light_position, glm::vec4 light_color,
    float ambient_strength, float diffuse_strength, float attenuation) {
    lightType=1;
    lightPos = light_position;
    lightDir = glm::vec3(0, 0, 0);
    lightColor= light_color;
    ambientStrength = ambient_strength;
    diffuseStrength = diffuse_strength;
    lightAttenuation = attenuation;
    cutOffAngle = 0.0f;

}

void GLpipeline::Light::CreateSpotLight(glm::vec3 light_position, glm::vec4 light_color,
    float ambient_strength, float diffuse_strength, float attenuation, float cutoff) {
    lightType=2;
    lightPos = light_position;
    lightDir = glm::vec3(0, 0, 0);
    lightColor= light_color;
    ambientStrength = ambient_strength;
    diffuseStrength = diffuse_strength;
    lightAttenuation = attenuation;
    cutOffAngle = cutoff;

}
/*
uniform int lightType[MAX_LIGHT_COUNT];//0=dir, 1= point, 2= spot
uniform vec3 lightPos[MAX_LIGHT_COUNT];
uniform vec3 lightDir[MAX_LIGHT_COUNT];
uniform vec4 lightColor[MAX_LIGHT_COUNT];
uniform float ambientStrength[MAX_LIGHT_COUNT];
uniform float diffuseStrength[MAX_LIGHT_COUNT];
uniform float lightAttenuation[MAX_LIGHT_COUNT];
uniform float lightAngle[MAX_LIGHT_COUNT];
*/

void GLpipeline::Light::SetupLights(std::vector<Light>& lights, GLuint shaderProgram) {
    int lightCount= lights.size();
    GLuint lightCountLocation= glGetUniformLocation(shaderProgram, "lightCount");
    glUniform1i(lightCountLocation, lightCount);
    int i=0;
    for (i; i<lightCount; i++) {
        GLuint lightTypeLocation= glGetUniformLocation(shaderProgram, std::format("lightType[{}]", i).c_str() );
        GLuint lightPosLocation= glGetUniformLocation(shaderProgram, std::format("lightPos[{}]", i).c_str() );
        GLuint lightDirLocation= glGetUniformLocation(shaderProgram,std::format("lightDir[{}]", i).c_str() );
        GLuint lightColorLocation= glGetUniformLocation(shaderProgram, std::format("lightColor[{}]", i).c_str() );
        GLuint ambientStrengthLocation= glGetUniformLocation(shaderProgram, std::format("ambientStrength[{}]", i).c_str() );
        GLuint diffuseStrengthLocation= glGetUniformLocation(shaderProgram, std::format("diffuseStrength[{}]", i).c_str() );
        GLuint lightAttenuationLocation= glGetUniformLocation(shaderProgram, std::format("lightAttenuation[{}]", i).c_str() );
        GLuint lightAngleLocation= glGetUniformLocation(shaderProgram, std::format("lightAngle[{}]", i).c_str() );

        //pass the data
        glUniform1f(lightTypeLocation, lights[i].lightType);
        glUniform3fv(lightPosLocation, 1, glm::value_ptr(lights[i].lightPos));
        glUniform3fv(lightDirLocation, 1, glm::value_ptr(lights[i].lightDir));
        glUniform4fv(lightColorLocation, 1, glm::value_ptr(lights[i].lightColor));
        glUniform1f(ambientStrengthLocation, lights[i].ambientStrength);
        glUniform1f(diffuseStrengthLocation, lights[i].diffuseStrength);
        glUniform1f(lightAttenuationLocation, lights[i].lightAttenuation);
        glUniform1f(lightAngleLocation, lights[i].cutOffAngle);

    }
}
