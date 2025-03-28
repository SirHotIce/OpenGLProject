#version 330

layout (location=0) in vec3 pos;//this it the location the ap is sending the data to
layout (location= 1) in vec2 UVin;
layout (location=2) in vec3 NormalsIn;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
out vec4 position;
out vec2 UVs;
out vec3 Normals;
out vec3 fragPos;
void main(){

    position= projection*view*model*vec4(pos,1.0);
    UVs=UVin;
    Normals= - mat3(transpose(inverse(model)))*NormalsIn;//normals were orignally filpped when imported. so we are filpping them back
    fragPos= (model*vec4(pos, 1.0)).xyz;
    gl_Position=position;
}