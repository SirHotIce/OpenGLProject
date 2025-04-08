//
// Created by Vin on 3/23/2025.
//

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <vector>
#include <GL/glew.h>

#include "CameraManager.h"
#include "Light.h"
#include "Material.h"
#include "ObjectTransform.h"
#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "ShadowMap.h"

namespace GLpipeline {
    class ObjectManager {
    private:
        GLuint VAO, VBO, IBO;
        ObjectTransform transform;
        Texture* texture;
        Mesh* mesh;
    public:

        GLuint* shaderProgram;
        //void SetupNormals();

        ObjectManager()=default;
        // ObjectManager(GLuint shader_program, const std::vector<GLfloat> &vPos, const std::vector<GLfloat> vUVs, Texture& _texture)
        //     : shaderProgram(shader_program), transform(), texture(_texture) {
        //
        //     int i=0;
        //     int numberOfVertices= vPos.size()/3;
        //     for (i; i<numberOfVertices; i++) {
        //         Vertex vertex;
        //         vertex.position= glm::vec3(vPos[i*3+0], vPos[i*3+1], vPos[i*3+2]);//3 floats per vertex
        //         vertex.UVs= glm::vec2(vUVs[i*2+0], vUVs[i*2+1]);///2 floats per vertex
        //         vertex.normals=glm::vec3(0.0f);
        //         vertices.push_back(vertex);
        //     }
        //     SetupNormals();
        //
        // }

        ObjectManager(GLuint& shader_program,  Mesh& _mesh, Texture& _texture)
            : shaderProgram(&shader_program),transform(), texture(&_texture), mesh(&_mesh) {
            // int i=0;
            // int numberOfVertices= vPos.size()/3;
            // for (i; i<numberOfVertices; i++) {
            //     Vertex vertex;
            //     vertex.position= glm::vec3(vPos[i*3+0], vPos[i*3+1], vPos[i*3+2]);//3 floats per vert
            //     vertex.UVs= glm::vec2(vUVs[i*2+0], vUVs[i*2+1]);//2 floats per vert
            //     vertex.normals=glm::vec3(0.0f);
            //     vertices.push_back(vertex);
            //
            // }
            PrimeObject();

        }

        ObjectTransform& getTransform(){return transform;}
        //void PrimeObjectNonIndexed();
        //void DrawObjectNonIndexed(CameraManager& camera, std::vector<Light>& lights, Material& material);
        void PrimeObject();
        void DrawObject(CameraManager& camera, std::vector<Light>& lights, Material& material);
        void DrawObjectWithShadows(CameraManager& camera, std::vector<Light>& lights, Material& material, ShadowMap& shadowMap);
        void DrawObjectToLight( Light light, GLuint& lightShader);
        void DestroyObject();
        ~ObjectManager(){DestroyObject();};

    };
}


#endif //OBJECTMANAGER_H
