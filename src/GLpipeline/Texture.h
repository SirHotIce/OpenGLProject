//
// Created by Vin on 3/25/2025.
//
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <iostream>
#ifndef TEXTURE_H
#define TEXTURE_H


namespace GLpipeline {
    class Texture {
    private:
        GLuint textureID;
        int width, height;
        int bitDepth;
        std::string filePath;

    public:
        Texture() {
            textureID=0;
            width=0, height=0;
            bitDepth=0;
            filePath="";
        }
        explicit Texture(const std::string &file_path)
            : filePath(file_path) {
            textureID=0;
            width=0, height=0;
            bitDepth=0;
        }

        void set_file_path(const std::string &file_path) {
            filePath = file_path;
        }

        void LoadTexture();
        void BindTexture(GLenum texUnit);
        void UnbindTexture();
        void ClearTexture();
        ~Texture() {
            UnbindTexture();
            ClearTexture();
        }
    };
}


#endif //TEXTURE_H
