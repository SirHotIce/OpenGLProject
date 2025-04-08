#version 330

layout (location=0) in vec3 pos;//this it the location the ap is sending the data to

uniform mat4 model;
uniform mat4 lightSpaceMatrix;
out vec4 position;
void main(){

    position= lightSpaceMatrix*model*vec4(pos,1.0);
    gl_Position=position;
}