#version 460 core

out vec4 color;
in vec3 Normal;
in vec3 viewPos;
in vec3 FragPos;
struct lightStruct {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        vec3 position;
};


uniform lightStruct Light_1;


struct matStruct {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float shinines;
};

uniform matStruct Mat_1;

void main() {
    //ambient//

    vec3 ambient = Light_1.ambient ;

    //difuse//

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(Light_1.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = Light_1.diffuse * (diff * Mat_1.diffuse);


    //specular//

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Mat_1.shinines);
    vec3 specular = Light_1.specular * (spec * Mat_1.specular);


    vec3 result = (ambient + diffuse); 
    color = vec4(result, 1.0);
}
