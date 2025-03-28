#version 330
//TODO: luminisence didt work use the dot prod of every light in the diffues to calculate the hatchings

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
uniform float linearAttenuation[MAX_LIGHT_COUNT];
uniform float exponentAttenuation[MAX_LIGHT_COUNT];
uniform float attenuationConstant[MAX_LIGHT_COUNT];
uniform float lightAngle[MAX_LIGHT_COUNT];

uniform float nearPlane;
uniform float farPlane;

float steps= 5;

float stepFactor(float inFactor){
    float stepFactor= 1/steps;
    float outFactor=floor(inFactor/stepFactor)*stepFactor;
    return outFactor;

}
float hatching(){
    float hatch1 = step(0.5, fract((position.x + position.y+fragPos.z) * 40.0));//tight hatching going up-right
   // float hatch2 = step(0.5, fract((-fragPos.x + fragPos.y) * 100.0));//tight hatching going up-left, returns 0 or 1 based on the position x, y
    float combined = hatch1;// * hatch2;
    return combined;

}
float calculateDiffuse(vec3 lightVector){
    float diffFactor=max(dot( normalize(Normals),normalize(lightVector)), 0.0f);
    if(diffFactor>0) {
        diffFactor=stepFactor(diffFactor);

    }
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
    if(specularFactor>0){
        specularFactor=stepFactor(specularFactor);
        return specularFactor;
    }else{
        return 0;
    }

}
vec4 CalculateLightValue(int lightIndex, vec3 direction){
    float diffuseFactor= calculateDiffuse(direction);
    vec4 specularColor= vec4(0.0f);
    float specularFactor=0;
    if(diffuseFactor>0){
        float specularFactor= calculateSpecular(direction);
        specularColor= vec4(1.0f)* specularFactor*material.specularIntensity;

    }
    vec4 white= vec4(1.0f);
    vec4 ambientColor= white*ambientStrength[lightIndex];
    vec4 diffuesColor= white*diffuseFactor*diffuseStrength[lightIndex];
    vec4 calculatedColor= ambientColor+diffuesColor+specularColor;
    float hatchFactor= 1.0f;
    if((diffuseFactor+specularFactor)<(2*(1/steps))){
        hatchFactor=hatching();
        calculatedColor*=hatchFactor;
    }

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
    vec4 fragmentLightColor= vec4(0);
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


float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

float edgeDetection(){
    float threshold= cos(radians(65));//for angle based
    //float threshold= 0.005;

    //depth based edge detection
    //float rawDepth= gl_FragCoord.z;
    //float linearDepth= LinearizeDepth(rawDepth);
    //float edge = fwidth(linearDepth);//depth based edge
    //float edge = length(fwidth(Normals));//checking the rapid change on the fragment normals
    float edge= dot(normalize(Normals),normalize(fragPos- cameraPosition)); //angle based
    if(edge>threshold){
        return 1.0f;
    }
    else{
        return 0.0f;
    }
}

vec4 finalHatchingFilter(vec4 unFiltered){
    float avgValue= (unFiltered.x+unFiltered.y+unFiltered.z)/3.0f;
    float threeshold= 0.2f;
    if(avgValue<=0.2f){
        return vec4(0);
    }else{
        return vec4(1);
    }
}
void main(){
    vec4 lightColors= CalculateLights();
    vec4 baseColor= texture(textureSample, UVs);
    //vec4 lit= baseColor*lightColors;

//    //check if hatching is needed
//    //multiple lights so easier solution is to use the brightness formula to check darkness of the fragment over dot product
//    //brightness = (R * 0.299) + (G * 0.587) + (B * 0.114)
//    float brightness= (lightColors.x*255.0f) * 0.299f+ (lightColors.y*255.0f) * 0.587f + (lightColors.z * 255.0f) * 0.114f;
//    //plan ~33% of the model to be hashed as those should be low enough
//    if(brightness<10.0f){
//        lit= lit*hatching();
//    }
    color=finalHatchingFilter(lightColors*edgeDetection())*baseColor;
    //color= vec4(normalize(Normals), 1.0f);
}