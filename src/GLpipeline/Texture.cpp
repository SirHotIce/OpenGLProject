//
// Created by Vin on 3/25/2025.
//

#include "Texture.h"

#include "../Utils/stb_image.h"

void GLpipeline::Texture::LoadTexture() {
    unsigned char* textureData= stbi_load(filePath.c_str(), &width ,&height,  &bitDepth
        , STBI_rgb_alpha);//always forcergba to make jpg images compatible

    if (!textureData) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);


    //setup filters
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//x-wrap repeat
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//y-wrap repeat
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//far blend linear
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//near blend linear

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);


    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(textureData);
}

void GLpipeline::Texture::BindTexture() {
    glActiveTexture(GL_TEXTURE0);//making texture  slot 0 active for binding
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void GLpipeline::Texture::UnbindTexture() {//clearup the slot 0 bound tex
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLpipeline::Texture::ClearTexture() {
    glDeleteTextures(1, &textureID);//delete texture from the graphic memeory
    textureID = 0;
    width=0;
    height=0;
    bitDepth=0;
    filePath="";
}
