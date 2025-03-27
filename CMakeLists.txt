cmake_minimum_required(VERSION 3.30)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


#create exe file
add_executable(OpenGLProject src/main.cpp
        src/GLinterface/Window.h
        src/GLinterface/InterfaceWindow.cpp
        src/GLinterface/InterfaceWindow.h
        src/GLpipeline/ShaderManager.cpp
        src/GLpipeline/ShaderManager.h
        src/GLpipeline/ObjectManager.cpp
        src/GLpipeline/ObjectManager.h
        src/GLpipeline/ErrorHandler.cpp
        src/GLpipeline/ErrorHandler.h
        src/GLpipeline/ObjectTransform.cpp
        src/GLpipeline/ObjectTransform.h
        src/GLpipeline/CameraManager.cpp
        src/GLpipeline/CameraManager.h
        src/GLinterface/InputSystem.cpp
        src/GLinterface/InputSystem.h
        src/Utils/stb_image.h
        src/GLpipeline/Texture.cpp
        src/GLpipeline/Texture.h
        src/GLpipeline/Light.cpp
        src/GLpipeline/Light.h
        src/GLpipeline/Material.cpp
        src/GLpipeline/Material.h
)
#link opengl
find_package(OpenGL REQUIRED)
target_include_directories(OpenGLProject PRIVATE external)
target_link_libraries(OpenGLProject OpenGL::GL)

#include and link glew
set(GLEW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/glew/include")
set(GLEW_LIBRARY "${CMAKE_SOURCE_DIR}/external/glew/lib/Release/X64")
set(GLEW_LIBRARY_FILE "${GLEW_LIBRARY}/glew32.lib")
set(GLEW_DLL "${PROJECT_SOURCE_DIR}/external/glew/bin/Release/x64/glew32.dll")

target_include_directories(OpenGLProject PRIVATE ${GLEW_INCLUDE_DIR})
target_link_libraries(OpenGLProject ${GLEW_LIBRARY_FILE})

# Copy GLEW DLL after build
add_custom_command(TARGET OpenGLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLEW_DLL}"
        $<TARGET_FILE_DIR:OpenGLProject>
)


#include and link glfw
set(GLFW3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/glfw/include")
set(GLFW3_LIBRARY "${CMAKE_SOURCE_DIR}/external/glfw/lib-vc2022")
set(GLFW3_LIBRARY_FILE "${GLFW3_LIBRARY}/glfw3.lib")
set(GLFW_DLL "${PROJECT_SOURCE_DIR}/external/glfw/lib-vc2022/glfw3.dll")
target_include_directories(OpenGLProject PRIVATE ${GLFW3_INCLUDE_DIR})
target_link_libraries(OpenGLProject ${GLFW3_LIBRARY_FILE})

# Copy GLFW DLL after build
add_custom_command(TARGET OpenGLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLFW_DLL}"
        $<TARGET_FILE_DIR:OpenGLProject>
)

#include and link assimp
set(ASSIMP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/assimp/include")
set(ASSIMP_LIBRARY "${CMAKE_SOURCE_DIR}/external/assimp/lib/x64")
set(ASSIMP_LIBRARY_FILE "${ASSIMP_LIBRARY}/assimp-vc143-mt.lib")
set(ASSIMP_DLL "${PROJECT_SOURCE_DIR}/external/assimp/bin/x64/assimp-vc143-mt.dll")
target_include_directories(OpenGLProject PRIVATE ${ASSIMP_INCLUDE_DIR})
target_link_libraries(OpenGLProject ${ASSIMP_LIBRARY_FILE})

# Copy GLFW DLL after build
add_custom_command(TARGET OpenGLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ASSIMP_DLL}"
        $<TARGET_FILE_DIR:OpenGLProject>
)
#incude glm dir
set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/glm")
target_include_directories(OpenGLProject PRIVATE ${GLM_INCLUDE_DIR})
# Copy shaders folder after build
set(SHADER_DIRECTORY "${CMAKE_SOURCE_DIR}/Shaders")
set(SHADER_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Shaders")

add_custom_command(TARGET OpenGLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${SHADER_OUTPUT_DIRECTORY}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${SHADER_DIRECTORY}" "${SHADER_OUTPUT_DIRECTORY}"
        COMMENT "Refreshing and copying shader folder..."
)
set(TEXTURE_DIRECTORY "${CMAKE_SOURCE_DIR}/Textures")
set(TEXTURE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Textures")

add_custom_command(TARGET OpenGLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${TEXTURE_OUTPUT_DIRECTORY}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${TEXTURE_DIRECTORY}" "${TEXTURE_OUTPUT_DIRECTORY}"
        COMMENT "Refreshing and copying texture folder..."
)



