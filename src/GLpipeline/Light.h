//
// Created by Vin on 3/27/2025.
//

#ifndef LIGHT_H
#define LIGHT_H
#include <iostream>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <format>
#include <string>
#include <glm/gtc/type_ptr.hpp>


namespace GLpipeline {
    class Light {

    private:
        int lightType;//0=dir, 1= point, 2= spot
        glm::vec3 lightPos;
        glm::vec3 lightDir;
        glm::vec4 lightColor;
        float ambientStrength;
        float diffuseStrength;
        float linearAtt;
        float exponentAtt;
        float attConstant;

        float cutOffAngle;
    public:
        Light()= default;
        void CreateDirectionalLight(glm::vec3 light_dir, glm::vec4 light_color,float ambient_strength, float diffuse_strength);
        void CreatePointLight(glm::vec3 light_position, glm::vec4 light_color, float ambient_strength, float diffuse_strength, float linear_att, float exponent_att, float att_constant);
        void CreateSpotLight(glm::vec3 light_dir, glm::vec3 light_position, glm::vec4 light_color, float ambient_strength, float diffuse_strength, float linear_att, float exponent_att, float att_cconstant ,float cutoff);

        static void SetupLights(std::vector<Light>& lights, GLuint shaderProgram);
        glm::mat4 GetLightMatrix();
        int GetLightType() {
            return lightType;
        }
    };
}


#endif //LIGHT_H
