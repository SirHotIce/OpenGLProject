//
// Created by Vin on 3/28/2025.
//

#ifndef BAISCMESHESS_H
#define BAISCMESHESS_H
#include <GL/glew.h>
#include <glm/glm.hpp>

#endif //BAISCMESHESS_H
namespace Utils {
    class BasicMeshes {
    public:
        static const std::vector<GLfloat> CubeVertices = {
            -0.5f, -0.5f, -0.5f, // 0: Left  Bottom Back
             0.5f, -0.5f, -0.5f,// 1: Right Bottom Back
             0.5f,  0.5f, -0.5f, // 2: Right Top    Back
            -0.5f,  0.5f, -0.5f, // 3: Left  Top    Back
            -0.5f, -0.5f,  0.5f, // 4: Left  Bottom Front
             0.5f, -0.5f,  0.5f, // 5: Right Bottom Front
             0.5f,  0.5f,  0.5f, // 6: Right Top    Front
            -0.5f,  0.5f,  0.5f  // 7: Left  Top    Front
        };
        static const std::vector<GLfloat> CubeUVs = {
            0.0f, 1.0f,// 0: Left  Bottom Back
            1.0f, 1.0f,// 1: Right Bottom Back
            1.0f, 0.0f,// 2: Right Top    Back
            0.0f, 0.0f,// 3: Left  Top    Back
            0.0f, 0.0f,// 4: Left  Bottom Front
            1.0f, 0.0f,// 5: Right Bottom Front
            1.0f, 1.0f,// 6: Right Top    Front
            0.0f, 1.0f // 7: Left  Top    Front
         };
        static const std::vector<GLuint> CubeIndices = {
            // Back face
            0, 1, 2,
            2, 3, 0,

            // Front face
            4, 5, 6,
            6, 7, 4,

            // Left faces
            0, 4, 7,
            7, 3, 0,

            // Right face
            1, 5, 6,
            6, 2, 1,

            // Bottom face
            0, 1, 5,
            5, 4, 0,

            // Top face
            3, 2, 6,
            6, 7, 3
        };

        static const std::vector<GLfloat> pyramidVerts = {
            -1.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };

        static const std::vector<GLfloat> pyramidUVs = {
            0.0f, 0.0f,
            0.5f, 0.0f,
            1.0f, 0.0f,
            0.5f, 1.0f
        };
        static const std::vector<GLuint> pyramidIndices = {
            0,3,1,
             1,3,2,
             2,3,0,
             0,1,2
         };
    };
}