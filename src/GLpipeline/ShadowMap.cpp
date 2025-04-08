//
// Created by Vin on 4/5/2025.
//

#include "ShadowMap.h"

#include "Texture.h"

void GLpipeline::ShadowMap::InitializeShadowMap(int width, int height) {
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &shadowMapTextureBuffer);
    glBindTexture(GL_TEXTURE_2D, shadowMapTextureBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
//this is usesd to pass data to the texture id, but we pass nullptr instead of data and data type would usually be unsigned bytes but we want the data to be in the form of float ie the depth data, this has primed the texture on the id to be able to to written to by the frame buffer, the texture id pointssz to the buffer where this needs to be written
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_WRAP_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_WRAP_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapTextureBuffer);
    //here we are attatching the texture to the current bound frame buffer so that when we use the frame buffer for a render pass this is used to write to hte texture instead of the viewport

    glDrawBuffer(GL_NONE);//we are saying we dont want to draw anything
    glReadBuffer(GL_NONE);//same her not reading any other data we are just writing the depth floats

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer is not complete\n: %i", status);
        return;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindBuffer(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
 return;
}

void GLpipeline::ShadowMap::WriteToShadowMap() {

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);//just enabling this framebuffer so that we can use it
}


void GLpipeline::ShadowMap::ReadShadowMap(GLenum textureUnit) {
    glActiveTexture(textureUnit);//instead of specifying GL_TEXTURE_0, 1... we willl pass it when we call
    glBindTexture(GL_TEXTURE_2D, shadowMapTextureBuffer);
}

void GLpipeline::ShadowMap::UnBind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindBuffer(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLpipeline::ShadowMap::~ShadowMap() {
    if (FBO) {
        glDeleteFramebuffers(1, &FBO);
    }
    if (shadowMapTextureBuffer) {
        glDeleteTextures(1, &shadowMapTextureBuffer);
    }
}
