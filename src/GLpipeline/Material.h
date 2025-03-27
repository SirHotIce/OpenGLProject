//
// Created by Vin on 3/27/2025.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "GL/glew.h"


namespace GLpipeline {
    class Material {
    private:
        float specularIntensity;
        float shininess;
    public:
        Material(float specular_intensity, float shininess)
            : specularIntensity(specular_intensity),
              shininess(shininess) {
        }
        void BindMaterial(GLuint shaderProgram);
    };
}


#endif //MATERIAL_H
