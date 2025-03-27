//
// Created by Vin on 3/23/2025.
//

#include "ShaderManager.h"

std::string GLpipeline::ShaderManager::ReadFile(std::string fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        printf("Error opening file %s\n", fileName.c_str());
        return "";
    }
    std::string line, data;
    while (std::getline(file,line)) {
        data+=line+="\n";
    }
    file.close();
    return data;
}
void GLpipeline::ShaderManager::AddShader(GLuint shaderProgram, GLuint shader, GLenum shaderType, std::string shaderSource) {
    shader= glCreateShader(shaderType);
    std::string readShader= ReadFile(shaderSource);
    const char* shaderCode= readShader.c_str();
    const GLchar* source= shaderCode;
    GLint shaderLength= strlen(source);
    glShaderSource(shader, 1, &source, &shaderLength);
    glCompileShader(shader);
    ErrorHandler::ValidateShader(shader, (shaderType==GL_VERTEX_SHADER)? VERTEX_SHADER_VALIDATION: FRAGMENT_SHADER_VALIDATION);
    glAttachShader(shaderProgram, shader);

}



void GLpipeline::ShaderManager::InitShader() {
    shaderProgram = glCreateProgram();
    if (shaderProgram == 0) {
        printf("Error creating shader program\n");
        exit(10);
    }
    AddShader(shaderProgram, vertexShader, GL_VERTEX_SHADER, vertexShaderSource);
    AddShader(shaderProgram, fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource);
    ErrorHandler::ValidateShader(shaderProgram, SHADER_PROGRAM_VALIDATION);
}

void GLpipeline::ShaderManager::DestroyShader() {
    if (vertexShader != 0) {
        glDeleteShader(vertexShader);
        vertexShader = 0;
    }
    if (fragmentShader != 0) {
        glDeleteShader(fragmentShader);
        fragmentShader = 0;
    }
    if (shaderProgram != 0) {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }
}
