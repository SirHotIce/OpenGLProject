//
// Created by Vin on 3/23/2025.
//

#include "ErrorHandler.h"

void GLpipeline::ErrorHandler::ValidateShader(GLuint &shader, ValidationTypeEnum validationType) {
    GLint result=0;
    GLchar error[1024]={""};

    if (validationType==SHADER_PROGRAM_VALIDATION) {
        //link error
        glLinkProgram(shader);
        glGetProgramiv(shader, GL_LINK_STATUS, &result);
        if (!result) {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
            printf("Shader program linking error\n%s\n", error);
            exit(10);
        }
        //validation error
        glValidateProgram(shader);
        glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
        if (!result) {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
            printf("Shader validation error\n%s\n", error);
            exit(10);
        }
    }

    //compile error

    if (validationType==VERTEX_SHADER_VALIDATION||validationType==FRAGMENT_SHADER_VALIDATION) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (!result) {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
            printf(
                "Shader compilation error on: %s\n%s\n",
                (validationType == VERTEX_SHADER_VALIDATION) ? "Vertex Shader" : "Fragment Shader",
                error
            );
            exit(10);
        }
    }
}
