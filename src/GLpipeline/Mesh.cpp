//
// Created by Vin on 3/27/2025.
//

#include "Mesh.h"

GLpipeline::Mesh::Mesh(const char *filename) {
    ImportMesh(filename);
}

void GLpipeline::Mesh::ImportMesh(const char *filename) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename,aiProcess_Triangulate| aiProcess_OptimizeMeshes |aiProcess_GenSmoothNormals);

    if (scene == nullptr) {
        printf("Error loading model %s\n%s", filename, importer.GetErrorString());

    }else {
        printf("Loaded %s\nHas %i meshes", filename, scene->mMeshes[0]->mNumVertices);
    }
    for (int i=0; i<scene->mMeshes[0]->mNumVertices; i++) {
        aiVector3D* vertex = &(scene->mMeshes[0]->mVertices[i]);
        Vertex vert;
        vert.position= glm::vec3(vertex->x, vertex->y, vertex->z);

        if (scene->mMeshes[0]->HasTextureCoords(0)) {
            printf("Texture coordinates: %f\n", vertex->x);
            aiVector3D* uv = &(scene->mMeshes[0]->mTextureCoords[0][i]);  // Only x and y are valid
            vert.UVs= glm::vec2(uv->x, uv->y);
        }
        aiVector3D* normal = &(scene->mMeshes[0]->mNormals[i]);
        vert.normals = glm::vec3(normal->x, normal->y, normal->z);
        vertices.push_back(vert);
    }
    for (int i= 0; i<scene->mMeshes[0]->mNumFaces; i++) {
        aiFace* face = &(scene->mMeshes[0]->mFaces[i]);
        for (int j= 0; j<face->mNumIndices; j++) {
            indices.push_back(face->mIndices[j]);
        }
    }



}

std::vector<GLpipeline::Mesh::Vertex> & GLpipeline::Mesh::GetVertices() {
    return vertices;
}

std::vector<GLuint> & GLpipeline::Mesh::GetIndices() {
    return indices;
}
