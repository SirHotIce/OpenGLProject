//
// Created by Vin on 3/23/2025.
//

#include "ObjectManager.h"

#include <string>
//
// void GLpipeline::ObjectManager::SetupNormals() {
//     int i=0;
//     int indexCount= indices.size();
//     for (i; i<indexCount; i+=3) {
//         int vec1Index= indices[i];//always calculate for this vertex as it is in i
//         int vec2Index= indices[i+1];
//         int vec3Index= indices[i+2];
//         glm::vec3 vec1 = vertices[vec2Index].position- vertices[vec1Index].position;//vector 2->1
//         glm::vec3 vec2 = vertices[vec3Index].position- vertices[vec1Index].position;//vector 3->1
//         glm::vec3 normal = normalize(glm::cross(vec1,vec2));
//         vertices[vec1Index].normals += normal;
//         vertices[vec2Index].normals += normal;
//         vertices[vec3Index].normals += normal;
//     }
//
//     for (Vertex& vert : vertices) {
//         vert.normals= glm::normalize(vert.normals);
//     }
//
// }
//
// void GLpipeline::ObjectManager::PrimeObjectNonIndexed() {
//     //VAO
//     glGenVertexArrays(1, &VAO);
//     glBindVertexArray(VAO);
//         //VBO
//         glGenBuffers(1, &VBO);
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
//         glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(Vertex)/*doing this to get the actual buffer size of the list and not just the number of elements, for an array size just gives the straight up memory size but vector returns the length and not the memory size*/
//             , vertices.data(), GL_STATIC_DRAW);
//         //Attrib pointer to pass VBO data
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);//here stride  is the size of each vertex so we want to step over it as we want new vertex, and it always is at top so offset is 0
//         //UV points
//             glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, UVs)));//we want to start at the UV of each vertex
//             glEnableVertexAttribArray(1);
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }
//
// void GLpipeline::ObjectManager::DrawObjectNonIndexed(CameraManager& camera, std::vector<Light>& lights, Material& material) {
//     glUseProgram(shaderProgram);
//         GLint modelLoc= glGetUniformLocation(shaderProgram, "model");//get the model locartion
//         GLint projLoc= glGetUniformLocation(shaderProgram, "projection");
//         GLint viewLoc= glGetUniformLocation(shaderProgram, "view");
//     GLint cameraPositionLocation= glGetUniformLocation(shaderProgram, "cameraPosition");
//     glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform.get_model()));
//     glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));
//     glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.get_updated_view()));
//     glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(camera.get_camera_position()));
//     material.BindMaterial(shaderProgram);
//     Light::SetupLights(lights, shaderProgram);
//     glBindVertexArray(VAO);
//                 glDrawArrays(GL_TRIANGLES, 0, vertices.size());//since 3 points make up a vertex
//         glBindVertexArray(0);
//     glUseProgram(0);
// }

void GLpipeline::ObjectManager::PrimeObject() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIndices().size()*sizeof(GLuint), mesh->GetIndices().data(), GL_STATIC_DRAW);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, mesh->GetVertices().size()*sizeof(Mesh::Vertex), mesh->GetVertices().data(), GL_STATIC_DRAW);

    //vertex points
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), 0);
                glEnableVertexAttribArray(0);
    //UV points
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)(offsetof(Mesh::Vertex, UVs)));
                glEnableVertexAttribArray(1);
    //Normals
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)(offsetof(Mesh::Vertex, normals)));
                glEnableVertexAttribArray(2);

    glBindVertexArray(0);

}

void GLpipeline::ObjectManager::DrawObject( CameraManager& camera, std::vector<Light>& lights, Material& material) {
    glUseProgram(*shaderProgram);
    texture->BindTexture();//use this tex to draw the model bound to tex slot 0
    GLint modelLoc= glGetUniformLocation(*shaderProgram, "model");
    GLint projLoc= glGetUniformLocation(*shaderProgram, "projection");
    GLint viewLoc= glGetUniformLocation(*shaderProgram, "view");
    GLint texLoc= glGetUniformLocation(*shaderProgram, "texture");
    GLint cameraPositionLocation= glGetUniformLocation(*shaderProgram, "cameraPosition");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform.get_model()));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.get_updated_view()));
    glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(camera.get_camera_position()));
    material.BindMaterial(*shaderProgram);
    Light::SetupLights(lights, *shaderProgram);

    //manga shader specific
    GLuint farPlaneLoc= glGetUniformLocation(*shaderProgram, "farPlane");
    GLuint nearPlaneLoc= glGetUniformLocation(*shaderProgram, "nearPlane");

    if (farPlaneLoc!=-1 && nearPlaneLoc!=-1) {
        glUniform1f(farPlaneLoc, camera.getFarPlane());
        glUniform1f(nearPlaneLoc, camera.getNearPlane());
    }

    glUniform1i(texLoc, 0);//telling the shader that the value for the uniform tex loc is 0
        glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, mesh->GetIndices().size(), GL_UNSIGNED_INT, 0);//no need to pass indices here as we have an already going IBO bound
        glBindVertexArray(0);
    texture->UnbindTexture();
    glUseProgram(0);

}


void GLpipeline::ObjectManager::DestroyObject() {
    if (VBO!=0) {
        glDeleteBuffers(1, &VBO);
        VBO=0;
    }
    if (IBO!=0) {
        glDeleteBuffers(1, &IBO);
        IBO=0;
    }
    if (VAO!=0) {
        glDeleteVertexArrays(1, &VAO);
        VAO=0;
    }
}
