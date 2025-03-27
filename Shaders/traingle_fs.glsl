#version 330

out vec4 color;
in vec4 position;
in vec2 UVs;
in vec3 Normals;
uniform sampler2D textureSample;
in vec3 fragPos;//just pure position data not based on projection or the view matrix only model
uniform vec3 cameraPosition;

struct Material{
    float specularIntensity;
    float shininess;

};
uniform Material material;
//light Data current max 8
#define MAX_LIGHT_COUNT 8
uniform int lightCount;
uniform int lightType[MAX_LIGHT_COUNT];//0=dir, 1= point, 2= spot
uniform vec3 lightPos[MAX_LIGHT_COUNT];
uniform vec3 lightDir[MAX_LIGHT_COUNT];
uniform vec4 lightColor[MAX_LIGHT_COUNT];
uniform float ambientStrength[MAX_LIGHT_COUNT];
uniform float diffuseStrength[MAX_LIGHT_COUNT];
uniform float lightAttenuation[MAX_LIGHT_COUNT];
uniform float lightAngle[MAX_LIGHT_COUNT];




float calculateDiffuse(vec3 lightVector){
    float diffFactor=max(dot(normalize(lightVector), normalize(Normals)), 0.0f);
    return diffFactor;


}
float calculateSpecular(vec3 lightVector){
    float specularFactor=0.0f;
    vec3 fragToEye= normalize( cameraPosition-fragPos);
    vec3 reflecedVector= normalize(reflect(lightVector, normalize(Normals)));
    specularFactor= max(dot(fragToEye, reflecedVector),0);
    if(specularFactor>0.0f){
        specularFactor= pow(specularFactor, material.shininess);
    }

    return specularFactor;
}
vec4 CalculateLights(){
    int i=0;
    vec4 fragmentLightColor;
    for(i;i<lightCount;i++){
        if(lightType[i]==0){
            //Dir Light
            vec4 ambientColor= lightColor[i]*ambientStrength[i];
            float diffuseFactor= calculateDiffuse(lightDir[i]);
            vec4 diffuesColor= lightColor[i]*diffuseFactor;
            vec4 specularColor= vec4(0.0f);
            if(diffuseFactor>0){
                float specularFactor= calculateSpecular(lightDir[i]);
                specularColor= vec4(1.0f)* specularFactor*material.specularIntensity;
            }

            fragmentLightColor+= ambientColor+diffuesColor+specularColor;


        }else if(lightType[i]==1){
            //point Light
        }else if(lightType[i]==2){
            //spot Light
        }
    }
    return fragmentLightColor;

}
void main(){

    vec4 litColors= CalculateLights();
    vec4 baseColor= texture(textureSample, UVs);
    color= baseColor*litColors;
    //color= vec4(normalize(Normals), 1.0f);
}