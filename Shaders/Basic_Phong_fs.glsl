#version 330

out vec4 color;
in vec4 position;
in vec2 UVs;
in vec3 Normals;
in vec4 directionalLightRefrence;
uniform sampler2D textureSample;//slot 0
uniform sampler2D shadowMap;//slot 1
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
uniform float linearAttenuation[MAX_LIGHT_COUNT];
uniform float exponentAttenuation[MAX_LIGHT_COUNT];
uniform float attenuationConstant[MAX_LIGHT_COUNT];
uniform float lightAngle[MAX_LIGHT_COUNT];


float CalcShadowFactor(int i){
    vec3 lightProjValue= directionalLightRefrence.xyz/directionalLightRefrence.w;//dividing by w normalizes the value to -1 to 1
    lightProjValue= (lightProjValue*0.5)+0.5; //this puts the value in 0 to 1 range
    float sampledDepth = texture(shadowMap, vec2(lightProjValue.x, lightProjValue.y)).r;//since the light proj is ortho z can be ignored and x value and y value normalized ot 0 to 1 will be acting as u and v, although depth exists it dowesnt look like it
    float currentFragDepthInLightSpace= lightProjValue.z;//gives the depth
    float bias= max( (0.05* dot(fragPos, lightDir[i])), 0.005);//to fix shadow acne
    float shadow=  (currentFragDepthInLightSpace-bias) >sampledDepth ?1.0:0.0;

    return shadow;
}

float calculateDiffuse(vec3 lightVector){
    float diffFactor=max(dot( normalize(Normals),normalize(lightVector)), 0.0f);
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

vec4 CalculateLightValue(int lightIndex, vec3 direction){
    vec4 ambientColor= lightColor[lightIndex]*ambientStrength[lightIndex];
    float diffuseFactor= calculateDiffuse(direction);
    vec4 diffuesColor= lightColor[lightIndex]*diffuseFactor*diffuseStrength[lightIndex];
    vec4 specularColor= vec4(0.0f);
    if(diffuseFactor>0){
        float specularFactor= calculateSpecular(direction);
        specularColor= vec4(1.0f)* specularFactor*material.specularIntensity;
    }

    float shadowFactor= CalcShadowFactor(lightIndex);
    vec4 calculatedColor= ambientColor+ ((1-shadowFactor)*(diffuesColor+specularColor));
    return calculatedColor;
}
vec4 CalculatePointLight(int i){
    vec3 directionLightToFragment= fragPos-lightPos[i];//vector of dir changes every fragment so we need to calculate it rather than justusing direction lik dirLight
    float distaceToLight= length(directionLightToFragment);
    vec4 totalLightColor= CalculateLightValue(i, normalize(directionLightToFragment));//we want direction normal , we are normalizing here as previously we needed its magnitude for length, if it was done befor ethe mag would be 1
    float attenuation= exponentAttenuation[i]*distaceToLight*distaceToLight + linearAttenuation[i]*distaceToLight + attenuationConstant[i];//1 is a constant to prevent the denom being 0
    vec4 finalColor= totalLightColor/attenuation;
    return finalColor;
}
vec4 CalculateLights(){
    int i=0;
    vec4 fragmentLightColor;
    for(i;i<lightCount;i++){

        switch(lightType[i])
        {
            case 0://dir
            fragmentLightColor+=CalculateLightValue(i, lightDir[i]);
            break;
            case 1://point
            fragmentLightColor+=CalculatePointLight(i);
            break;
            case 2://spot
            vec3 lightVec= fragPos-lightPos[i];
            vec4 pointOnlyColor= CalculatePointLight(i);

            float sptEdge= cos(lightAngle[i]);
            float sptFactor= dot(normalize(lightVec), normalize(lightDir[i]));
            vec4 finalColor= vec4(0.0f);

            if(sptFactor<sptEdge){
                float finalSptFactor= 1-(sptFactor*(1/1-sptEdge));
                finalColor= pointOnlyColor*finalSptFactor;
            }

            fragmentLightColor+=finalColor;

            break;
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