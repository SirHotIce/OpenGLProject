//
// Created by Vin on 4/5/2025.
//

#ifndef SHADOWMAP_H
#define SHADOWMAP_H
#include <GL/glew.h>


namespace GLpipeline {
    class ShadowMap {
    public:
        ShadowMap() {
            FBO=0;
            shadowMapTextureBuffer = 0;
        }

        ~ShadowMap();

        void InitializeShadowMap(int width, int height);
        void WriteToShadowMap();
        void ReadShadowMap(GLenum textureUnit);
        void UnBind();

        GLuint& GetShadowMap() {
            return shadowMapTextureBuffer;
        }
    private:
        GLuint FBO, shadowMapTextureBuffer;
        GLuint shadowMapWidth, shadowMapHeight;
    };
}


#endif //SHADOWMAP_H
