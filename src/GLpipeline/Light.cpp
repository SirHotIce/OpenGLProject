//
// Created by Vin on 3/27/2025.
//

#include "Light.h"



void GLpipeline::Light::CreateDirectionalLight(glm::vec3 light_dir, glm::vec4 light_color, float ambient_strength,
                                               float diffuse_strength) {
    lightType=0;
    lightDir = light_dir;
    lightColor= light_color;
    ambientStrength = ambient_strength;
    diffuseStrength = diffuse_strength;
    lightPos = glm::vec3(0, 0, 0);
    linearAtt=0.0f;
    exponentAtt=0.0f;
    cutOffAngle= 0.0f;
    attConstant=0.0f;
}

void GLpipeline::Light::CreatePointLight(glm::vec3 light_position, glm::vec4 light_color,
    float ambient_strength, float diffuse_strength,float linear_att, float exponent_att, float att_constant) {
    lightType=1;
    lightPos = light_position;
    lightDir = glm::vec3(0, 0, 0);
    lightColor= light_color;
    ambientStrength = ambient_strength;
    diffuseStrength = diffuse_strength;
    linearAtt= linear_att;
    exponentAtt= exponent_att;
    cutOffAngle = 0.0f;
    attConstant = att_constant;

}

void GLpipeline::Light::CreateSpotLight(glm::vec3 light_dir, glm::vec3 light_position, glm::vec4 light_color,
    float ambient_strength, float diffuse_strength, float linear_att, float exponent_att, float att_constant,float cutoff) {
    lightType=2;
    lightPos = light_position;
    lightDir = light_dir;
    lightColor= light_color;
    ambientStrength = ambient_strength;
    diffuseStrength = diffuse_strength;
    linearAtt= linear_att;
    exponentAtt= exponent_att;
    cutOffAngle = cutoff;
    attConstant= att_constant;

}
/*
uniform int lightType[MAX_LIGHT_COUNT];//0=dir, 1= point, 2= spot
uniform vec3 lightPos[MAX_LIGHT_COUNT];
uniform vec3 lightDir[MAX_LIGHT_COUNT];
uniform vec4 lightColor[MAX_LIGHT_COUNT];
uniform float ambientStrength[MAX_LIGHT_COUNT];
uniform float diffuseStrength[MAX_LIGHT_COUNT];
uniform float linearAttenuation[MAX_LIGHT_COUNT];
uniform float exponentAttenuation[MAX_LIGHT_COUNT];
uniform float attenuationConstant[MAX_LIGHT_COUNT];
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
        GLuint linearAttenLocation= glGetUniformLocation(shaderProgram, std::format("linearAttenuation[{}]", i).c_str() );
        GLuint expAttenLocation= glGetUniformLocation(shaderProgram, std::format("exponentAttenuation[{}]", i).c_str() );
        GLuint lightAngleLocation= glGetUniformLocation(shaderProgram, std::format("lightAngle[{}]", i).c_str() );
        GLuint attenuationConstantLocation= glGetUniformLocation(shaderProgram, std::format("attenuationConstant[{}]", i).c_str() );

        //pass the data
        glUniform1i(lightTypeLocation, lights[i].lightType);
        glUniform3fv(lightPosLocation, 1, glm::value_ptr(lights[i].lightPos));
        glUniform3fv(lightDirLocation, 1, glm::value_ptr(lights[i].lightDir));
        glUniform4fv(lightColorLocation, 1, glm::value_ptr(lights[i].lightColor));
        glUniform1f(ambientStrengthLocation, lights[i].ambientStrength);
        glUniform1f(diffuseStrengthLocation, lights[i].diffuseStrength);
        glUniform1f(linearAttenLocation, lights[i].linearAtt);
        glUniform1f(expAttenLocation, lights[i].exponentAtt);
        glUniform1f(attenuationConstantLocation, lights[i].attConstant);
        glUniform1f(lightAngleLocation, glm::radians(lights[i].cutOffAngle));

    }

}

glm::mat4 GLpipeline::Light::GetLightMatrix() {
    //create the lightspace matrix
    glm::mat4 lightProjection= glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
    //the view vec will be ust the light to the origin with world up
    glm::mat4 lightView= glm::lookAt(lightDir, glm::vec3(0), glm::vec3(0, 1, 0));
    glm::mat4 lightSpaceMatrix= lightProjection * lightView;
    return lightSpaceMatrix;
}
