//
// Created by Vin on 3/23/2025.
//

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <string>
#include <GL/glew.h>
#include <fstream>
#include "ErrorHandler.h"


namespace GLpipeline {
    class ShaderManager {
    private:
        GLuint shaderProgram, fragmentShader, vertexShader;
        std::string vertexShaderSource, fragmentShaderSource;
        std::string ReadFile(std::string fileName);
        void AddShader(GLuint shaderProgram, GLuint shader, GLenum shaderType, std::string shaderSource);
    public:
        ShaderManager(const std::string &vertex_shader_source, const std::string &fragment_shader_source)
            : vertexShaderSource(vertex_shader_source),
              fragmentShaderSource(fragment_shader_source) {
        }

          GLuint shader_program() const {
            return shaderProgram;
        }

          GLuint fragment_shader() const {
            return fragmentShader;
        }

          GLuint vertex_shader() const {
            return vertexShader;
        }

        void InitShader();
        void DestroyShader();

        ~ShaderManager() {DestroyShader();};
    };
}


#endif //SHADERMANAGER_H
