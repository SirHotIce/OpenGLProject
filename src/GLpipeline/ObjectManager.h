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

namespace GLpipeline {
    class ObjectManager {
    private:
        GLuint VAO, VBO, IBO;
        ObjectTransform transform;
        Texture texture;
    public:
        struct Vertex {
            glm::vec3 position;
            glm::vec2 UVs;
            glm::vec3 normals;

        };
        GLuint shaderProgram;
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        void SetupNormals();

        ObjectManager(GLuint shader_program, const std::vector<GLfloat> &vPos, const std::vector<GLfloat> vUVs, Texture& _texture)
            : shaderProgram(shader_program), transform(), texture(_texture) {

            int i=0;
            int numberOfVertices= vPos.size()/3;
            for (i; i<numberOfVertices; i++) {
                Vertex vertex;
                vertex.position= glm::vec3(vPos[i*3+0], vPos[i*3+1], vPos[i*3+2]);//3 floats per vertex
                vertex.UVs= glm::vec2(vUVs[i*2+0], vUVs[i*2+1]);///2 floats per vertex
                vertex.normals=glm::vec3(0.0f);
                vertices.push_back(vertex);
            }
            SetupNormals();

        }

        ObjectManager(GLuint shader_program, const std::vector<GLfloat> &vPos, std::vector<GLfloat> vUVs, const std::vector<GLuint> &indices, Texture& _texture)
            : shaderProgram(shader_program),
              indices(indices),transform(), texture(_texture){
            int i=0;
            int numberOfVertices= vPos.size()/3;
            for (i; i<numberOfVertices; i++) {
                Vertex vertex;
                vertex.position= glm::vec3(vPos[i*3+0], vPos[i*3+1], vPos[i*3+2]);//3 floats per vert
                vertex.UVs= glm::vec2(vUVs[i*2+0], vUVs[i*2+1]);//2 floats per vert
                vertex.normals=glm::vec3(0.0f);
                vertices.push_back(vertex);

            }
            SetupNormals();

        }

        ObjectTransform& getTransform(){return transform;}
        void TestTransform();
        void Draw();
        void PrimeObjectNonIndexed();
        void DrawObjectNonIndexed(CameraManager& camera, std::vector<Light>& lights, Material& material);
        void PrimeObjectIndexed();
        void DrawObjectIndexed(CameraManager& camera, std::vector<Light>& lights, Material& material);
        void DestroyObject();

        ~ObjectManager(){DestroyObject();};

    };
}


#endif //OBJECTMANAGER_H
