
//
// Created by Vin on 3/23/2025.
//

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#include <string>
#include <GL/glew.h>
namespace GLpipeline {
    enum ValidationTypeEnum {
        SHADER_PROGRAM_VALIDATION,
        VERTEX_SHADER_VALIDATION,
        FRAGMENT_SHADER_VALIDATION,
    };
    class ErrorHandler {
    public:
        static void ValidateShader(GLuint &shader, ValidationTypeEnum validationType);
    };
}


#endif //ERRORHANDLER_H
