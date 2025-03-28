//
// Created by Vin on 3/27/2025.
//

#ifndef MESH_H
#define MESH_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>


namespace GLpipeline {
    class Mesh {
    public:
        struct Vertex {
            glm::vec3 position;
            glm::vec2 UVs;
            glm::vec3 normals;
        };
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;

        Mesh(const char* filename);
        void ImportMesh(const char* filename);
        std::vector<Vertex>&  GetVertices();
        std::vector<GLuint>&  GetIndices();
    };


}


#endif //MESH_H
